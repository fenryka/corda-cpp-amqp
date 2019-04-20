#include "CompositeFactory.h"

#include <iostream>
#include <vector>
#include <set>

#include "consumer/PropertyReader.h"

/******************************************************************************/

template <typename T>
std::shared_ptr<T>
computeIfAbsent (
    spStrMap_t<T> & map_,
    const std::unique_ptr<amqp::internal::schema::Field> & k_,
    std::function<std::shared_ptr<T>(void)> f_
) {
    auto it = map_.find (k_->type());

    if (it == map_.end()) {
        map_[k_->type()] = std::move (f_());

        return map_[k_->type()];
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

        if (m_compositeReadersByType.find (i->first) ==
                m_compositeReadersByType.end()
        ) {
            m_compositeReadersByType[i->first] = process__(i, l);
        }

        m_compositeReadersByDescriptor[i->second->descriptor()] =
            m_compositeReadersByType[i->first];
    }
}

/******************************************************************************/

std::shared_ptr<amqp::CompositeReader>
CompositeFactory::process__ (
    upStrMap_t<amqp::internal::schema::Composite>::const_iterator schema_,
    std::set<std::string> & history_
) {
    history_.insert (schema_->first);
    std::vector<std::weak_ptr<amqp::Reader>> readers;

    auto & fields = schema_->second->fields();

    readers.reserve(fields.size());

    for (const auto & field : fields) {
        if (field->primitive()) {
            auto reader = computeIfAbsent<amqp::PropertyReader> (
                m_propertyReaders,
                field,
                [&field] () -> std::shared_ptr<amqp::PropertyReader> {
                    return amqp::PropertyReader::make (field);
                });

            readers.emplace_back (reader);
        } else {
            auto reader = computeIfAbsent<amqp::CompositeReader> (
                m_compositeReadersByType,
                field,
                [ &schema_, &history_, this ]() -> std::shared_ptr<amqp::CompositeReader> {
                    auto rtn = process__ (++schema_, history_);

                    m_compositeReadersByDescriptor[schema_->second->descriptor()] =
                        m_compositeReadersByType[schema_->first];

                    return rtn;
                });

            readers.emplace_back (reader);
        }
    }

    return std::make_shared<amqp::CompositeReader> (readers);
}

/******************************************************************************/

const std::shared_ptr<amqp::CompositeReader>
CompositeFactory::byType (const std::string & type_) {
    std::cout << "BY TYPE: " << type_ << std::endl;

    auto it = m_compositeReadersByType.find (type_);

    return (it == m_compositeReadersByType.end()) ? nullptr : it->second;
}

/******************************************************************************/

const std::shared_ptr<amqp::CompositeReader>
CompositeFactory::byDescriptor (const std::string & descriptor_) {
    auto it = m_compositeReadersByDescriptor.find (descriptor_);

    return (it == m_compositeReadersByDescriptor.end()) ? nullptr : it->second;
}

/******************************************************************************/
