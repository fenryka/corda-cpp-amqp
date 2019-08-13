#include "CompositeFactory.h"

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include <assert.h>

#include "debug.h"

#include "consumer/Reader.h"
#include "consumer/PropertyReader.h"
#include "consumer/CompositeReader.h"
#include "consumer/RestrictedReader.h"

#include "schema/restricted-types/List.h"

/******************************************************************************/

/**
 *
 */
template <typename T>
std::shared_ptr<T> &
computeIfAbsent (
    spStrMap_t<T> & map_,
    const std::string & k_,
    std::function<std::shared_ptr<T>(void)> f_
) {
    auto it = map_.find (k_);

    if (it == map_.end()) {
        DBG ("ComputeIfAbsent \"" << k_ << "\" - missing" << std::endl);
        map_[k_] = std::move (f_());
        DBG ("                \"" << k_ << "\" - RTN: " << map_[k_]->name() << " : " << map_[k_]->type() << std::endl);
        assert (map_[k_]);
        assert (map_[k_] != nullptr);
        assert (k_ == map_[k_]->type());

        return map_[k_];
    }
    else {
        DBG ("ComputeIfAbsent \"" << k_ << "\" - found it" << std::endl);
        DBG ("                \"" << k_ << "\" - RTN: " << map_[k_]->name() << std::endl);

        assert (it->second != nullptr);

        return it->second;
    }
}

/******************************************************************************
 *
 *  CompositeFactory
 *
 ******************************************************************************/

/**
 *
 * Walk through the types in a Schema and produce readers for them
 *
 */
void
CompositeFactory::process (const SchemaPtr & schema_) {
    for (auto i = schema_->begin() ; i != schema_->end() ; ++i) {
        for (const auto & j : *i) {
            process(*j);
            m_readersByDescriptor[j->descriptor()] = m_readersByType[j->name()];
        }

    }
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::process(
        const amqp::internal::schema::AMQPTypeNotation & schema_)
{
    std::cout << "PROCESS: " << schema_.name() << std::endl;

    return computeIfAbsent<amqp::Reader> (
        m_readersByType,
        schema_.name(),
        [& schema_, this] () -> std::shared_ptr<amqp::Reader> {
            switch (schema_.type()) {
                case amqp::internal::schema::AMQPTypeNotation::Composite : {
                    return processComposite(schema_);
                }
                case amqp::internal::schema::AMQPTypeNotation::Restricted : {
                    return processRestricted(schema_);
                }
            }
        });
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processComposite (
        const amqp::internal::schema::AMQPTypeNotation & type_)
{
    std::cout << "PROCESS COMPOSITE: " << type_.name() << std::endl;

    std::vector<std::weak_ptr<amqp::Reader>> readers;

    auto & fields = dynamic_cast<const amqp::internal::schema::Composite &> (
            type_).fields();

    readers.reserve(fields.size());

    for (const auto & field : fields) {
        DBG ("  Field: " << field->name() << ": " << field->type() << std::endl);

        switch (field->fieldType()) {
            case amqp::internal::schema::FieldType::PrimitiveProperty : {
                auto reader = computeIfAbsent<amqp::Reader>(
                        m_readersByType,
                        field->type(),
                        [&field]() -> std::shared_ptr<amqp::PropertyReader> {
                            return amqp::PropertyReader::make(field);
                        });

                assert (reader);
                readers.emplace_back(reader);
                assert (readers.back().lock());
                break;
            }
            case amqp::internal::schema::FieldType::CompositeProperty :
            case amqp::internal::schema::FieldType::RestrictedProperty :  {
                auto reader = m_readersByType[field->type()];

                assert (reader);
                readers.emplace_back(reader);
                assert (readers.back().lock());
                break;
            }
        }

        assert (readers.back().lock());
    }

    return std::make_shared<amqp::CompositeReader> (type_.name(), readers);
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processRestricted (
        const amqp::internal::schema::AMQPTypeNotation & type_)
{
    std::cout << "PROCESS RESTRICTED: " << type_.name() << std::endl;
}

/******************************************************************************/
/*
std::shared_ptr<amqp::Reader>
CompositeFactory::processRestricted(
    amqp::internal::schema::Schema::SchemaSet::const_iterator schema_,
    std::set<std::string> & history_)
{
    DBG ("processRestricted - " << (*schema_)->name() << std::endl);
    auto * restricted = dynamic_cast<amqp::internal::schema::Restricted *> (
            schema_->get());

    if (restricted->restrictedType() ==
            amqp::internal::schema::Restricted::RestrictedTypes::List)
    {
        auto * list = dynamic_cast<amqp::internal::schema::List *> (restricted);

        DBG ("Processing List - " << list->listOf() << std::endl);

        if (amqp::internal::schema::Field::typeIsPrimitive(list->listOf())) {
            DBG ("  List of Primitives" << std::endl);
            auto reader = computeIfAbsent<amqp::Reader> (
                    m_readersByType,
                    list->listOf(),
                    [& list] () -> std::shared_ptr<amqp::PropertyReader> {
                        return amqp::PropertyReader::make (list->listOf());
                    });

            return std::make_shared<amqp::ListReader> ((*schema_)->name(), reader);
        } else {
            DBG ("  List of Composite - " << list->listOf() << std::endl);
            auto reader = computeIfAbsent<amqp::Reader> (
                    m_readersByType,
                    list->listOf(),
                    [ &schema_, &history_, this ]() -> std::shared_ptr<amqp::Reader> {
                        return process (++schema_, history_);
                    });

            return std::make_shared<amqp::ListReader> ((*schema_)->name(), reader);
        }
    }

    DBG ("  ProcessRestricted: Returning nullptr");
    return nullptr;
}
 */

/******************************************************************************/
/*
std::shared_ptr<amqp::Reader>
CompositeFactory::processComposite (
    amqp::internal::schema::Schema::SchemaSet::const_iterator schema_,
    std::set<std::string> & history_
) {
    DBG ("processComposite  - " << (*schema_)->name() << std::endl);

    history_.insert ((*schema_)->name());
    std::vector<std::weak_ptr<amqp::Reader>> readers;

    auto & fields = dynamic_cast<amqp::internal::schema::Composite *> (
            schema_->get())->fields();

    readers.reserve(fields.size());

    for (const auto & field : fields) {
        DBG ("  Field: " << field->name() << ": " << field->type() << std::endl);

        switch (field->fieldType()) {
            case amqp::internal::schema::FieldType::PrimitiveProperty : {
                auto reader = computeIfAbsent<amqp::Reader>(
                        m_readersByType,
                        field->type(),
                        [&field]() -> std::shared_ptr<amqp::PropertyReader> {
                            return amqp::PropertyReader::make(field);
                        });

                assert (reader);
                readers.emplace_back(reader);
                assert (readers.back().lock());
                break;
            }
            case amqp::internal::schema::FieldType::CompositeProperty : {
                auto reader = computeIfAbsent<amqp::Reader>(
                        m_readersByType,
                        field->type(),
                        [&schema_, &history_, this]() -> std::shared_ptr<amqp::Reader> {
                            return process (++schema_, history_);
                        });

                assert (reader);
                readers.emplace_back(reader);
                assert (readers.back().lock());
                break;
            }

            case amqp::internal::schema::FieldType::RestrictedProperty :  {
                auto reader = computeIfAbsent<amqp::Reader> (
                        m_readersByType,
                        field->requires().front(),
                        [ &schema_, &history_, this ]() -> std::shared_ptr<amqp::Reader> {
                            return process (++schema_, history_);
                        });

                assert (reader);
                readers.emplace_back (reader);
                assert (readers.back().lock());
                break;
            }
        }

        assert (readers.back().lock());
    }

    return std::make_shared<amqp::CompositeReader> ((*schema_)->name(), readers);
}
*/
/******************************************************************************/

const std::shared_ptr<amqp::Reader>
CompositeFactory::byType (const std::string & type_) {
    auto it = m_readersByType.find (type_);

    return (it == m_readersByType.end()) ? nullptr : it->second;
}

/******************************************************************************/

const std::shared_ptr<amqp::Reader>
CompositeFactory::byDescriptor (const std::string & descriptor_) {
    auto it = m_readersByDescriptor.find (descriptor_);

    return (it == m_readersByDescriptor.end()) ? nullptr : it->second;
}

/******************************************************************************/
