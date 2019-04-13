#include "CompositeFactory.h"

#include <iostream>
#include <vector>

#include "consumer/PropertyReader.h"

/******************************************************************************/

/**
 *
 * Walk through the types in a Schema and produce readers for them
 *
 */
void
CompositeFactory::process (const SchemaPtr & schema) {
    std::cout << "PROCESS" << std::endl;

    for (auto const & type : schema->types()) {
        process (type.second);
    }
}

/******************************************************************************/

std::unique_ptr<amqp::CompositeReader>
CompositeFactory::process (const CompositePtr & schema) {
    std::vector<std::unique_ptr<amqp::StringReader>> readers;

    auto & fields (schema->fields());

    readers.reserve(fields.size());

    for (const auto & field : fields) {
        std::cout << "field: " << field->name() << " : " << field->type() << std::endl;

        if (field->primitive()) {
            readers.emplace_back (amqp::PropertyReader::make (field));
        }
    }

    return std::make_unique<amqp::CompositeReader> ();
}

/******************************************************************************/

