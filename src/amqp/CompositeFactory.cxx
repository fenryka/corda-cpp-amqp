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

/******************************************************************************/

namespace {

    std::pair<std::string, std::string>
    listType (const std::string & list_) {
        auto pos = list_.find ('<');

        return std::make_pair (
                std::string { list_.substr (0, pos) },
                std::string { list_.substr(pos + 1, list_.size() - pos - 2) }
        );
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
    // Deals with hitting a recursive loop in our type hierarchy, at the moment
    // if we find a loop we'll die on our arse... later on we might want to do
    // something a bit smarter than shitting the bed!.
    std::set<std::string> l;

    for (auto i = schema_->begin() ; i != schema_->end() ; ++i) {
        l.clear();

        process(i, l);

        m_readersByDescriptor[(*i)->descriptor()] = m_readersByType[(*i)->name()];
    }
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::process(
    amqp::internal::schema::Schema::const_iterator schema_,
    std::set<std::string> & history_)
{
    DBG ("\nProcess: " << (*schema_)->name() << std::endl);

    return computeIfAbsent<amqp::Reader> (
        m_readersByType,
        (*schema_)->name(),
        [&schema_, this, &history_] () -> std::shared_ptr<amqp::Reader> {
            switch ((*schema_)->type()) {
                case amqp::internal::schema::AMQPTypeNotation::Composite : {
                    return processComposite(schema_, history_);
                }
                case amqp::internal::schema::AMQPTypeNotation::Restricted : {
                    return processRestricted(schema_, history_);
                }
            }
        });
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processRestricted(
    amqp::internal::schema::Schema::const_iterator schema_,
    std::set<std::string> & history_)
{
    DBG ("processRestricted - " << (*schema_)->name() << std::endl);
    auto * restricted = dynamic_cast<amqp::internal::schema::Restricted *> (
            schema_->get());

    if (restricted->restrictedType() ==
            amqp::internal::schema::Restricted::RestrictedTypes::List)
    {
        auto split = listType(restricted->name());

        DBG ("Processing List - "
            << split.first
            << " :: "
            << split.second
            << std::endl);

        if (amqp::internal::schema::Field::typeIsPrimitive(split.second)) {
            DBG ("  List of Primitives" << std::endl);
            auto reader = computeIfAbsent<amqp::Reader> (
                    m_readersByType,
                    split.second,
                    [&split] () -> std::shared_ptr<amqp::PropertyReader> {
                        return amqp::PropertyReader::make (split.second);
                    });

            return std::make_shared<amqp::ListReader> ((*schema_)->name(), reader);
        } else {
            DBG ("  List of Composite - " << split.second << std::endl);
            auto reader = computeIfAbsent<amqp::Reader> (
                    m_readersByType,
                    split.second,
                    [ &schema_, &history_, this ]() -> std::shared_ptr<amqp::Reader> {
                        return process (++schema_, history_);
                    });

            return std::make_shared<amqp::ListReader> ((*schema_)->name(), reader);
        }
    }

    DBG ("  ProcessRestricted: Returning nullptr");
    return nullptr;
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processComposite (
    amqp::internal::schema::Schema::const_iterator schema_,
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
