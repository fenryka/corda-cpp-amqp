#include "CompositeFactory.h"

#include <set>
#include <vector>
#include <iostream>

#include "consumer/PropertyReader.h"
#include "consumer/CompositeReader.h"
#include "consumer/RestrictedReader.h"

/******************************************************************************/

/**
 *
 * @tparam T
 * @param map_
 * @param k_
 * @param f_
 * @return
 */
template <typename T>
std::shared_ptr<T>
computeIfAbsent (
    spStrMap_t<T> & map_,
    const std::string & k_,
    std::function<std::shared_ptr<T>(void)> f_
) {
    auto it = map_.find (k_);

    if (it == map_.end()) {
        map_[k_] = std::move (f_());

        return map_[k_];
    }
    else {
        return it->second;
    }
}

/******************************************************************************/

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

        m_readersByDescriptor[i->second->descriptor()] =
                m_readersByType[i->first];
    }

}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::process(
        upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator schema_,
        std::set<std::string> & history_)
{
    std::cout << "Find type and process: " << schema_->first << " " <<  std::endl;

    return computeIfAbsent<amqp::Reader> (
            m_readersByType,
            schema_->first,
            [&schema_, this, &history_] () -> std::shared_ptr<amqp::Reader> {
                switch (schema_->second->type()) {
                    case amqp::internal::schema::AMQPTypeNotation::Composite : {
                        return processComposite(schema_, history_);
                    }
                    case amqp::internal::schema::AMQPTypeNotation::Restricted : {
                        return processRestricted(schema_, history_);
                    }
                }
                return nullptr;
            });
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processRestricted(
    upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator,
    std::set<std::string> &)
{
    std::cout << "Add restricted type" << std::endl;
    return std::make_shared<amqp::RestrictedReader>();
}

/******************************************************************************/

std::shared_ptr<amqp::Reader>
CompositeFactory::processComposite (
    upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator schema_,
    std::set<std::string> & history_
) {
    history_.insert (schema_->first);
    std::vector<std::weak_ptr<amqp::Reader>> readers;

    auto & fields = dynamic_cast<amqp::internal::schema::Composite *> (
            schema_->second.get())->fields();

    readers.reserve(fields.size());


    for (const auto & field : fields) {
        switch (field->fieldType()) {
            case amqp::internal::schema::FieldType::PrimitiveProperty : {
                auto reader = computeIfAbsent<amqp::PropertyReader> (
                    m_propertyReaders,
                    field->type(),
                    [&field] () -> std::shared_ptr<amqp::PropertyReader> {
                        return amqp::PropertyReader::make (field);
                    });

                readers.emplace_back (reader);
                break;
            }
            case amqp::internal::schema::FieldType::CompositeProperty :
            case amqp::internal::schema::FieldType::RestrictedProperty :  {
                auto reader = computeIfAbsent<amqp::Reader> (
                    m_readersByType,
                    field->type(),
                    [ &schema_, &history_, this ]() -> std::shared_ptr<amqp::Reader> {
                        return process (++schema_, history_);
                    });

                readers.emplace_back (reader);
                break;
            }
        }
    }

    return std::make_shared<amqp::CompositeReader> (readers);
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
