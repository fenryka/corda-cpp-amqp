#include "CompositeFactory.h"

#include <iostream>
#include <vector>

#include "consumer/PropertyReader.h"

/******************************************************************************/

template <typename T>
std::shared_ptr<T>
computeIfAbsent (
        StrPtrMap<T> & map_,
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
CompositeFactory::process (const SchemaPtr & schema) {
    for (auto const & type : schema->types()) {
        std::cout << "PROCESS: " << type.first << " " << type.second->descriptor() << std::endl;

        auto reader = process (type.second);


        m_compositeReadersByType[type.first] = reader;
        m_compositeReadersByDescriptor[type.second->descriptor()] = reader;
    }
}

/******************************************************************************/

std::shared_ptr<amqp::CompositeReader>
CompositeFactory::process (const CompositePtr & schema) {
    std::vector<std::shared_ptr<amqp::Reader>> readers;

    auto & fields (schema->fields());

    readers.reserve(fields.size());

    for (const auto & field : fields) {
        std::cout << "field: " << field->name() << " : " << field->type() << std::endl;

        if (field->primitive()) {
            auto reader = computeIfAbsent<amqp::PropertyReader> (
                m_propertyReaders,
                field,
                [&field] () -> std::shared_ptr<amqp::PropertyReader> {
                    return amqp::PropertyReader::make (field);
                });

            readers.emplace_back (reader);
        } else {
            readers.emplace_back (m_compositeReadersByType[field->type()]);
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
