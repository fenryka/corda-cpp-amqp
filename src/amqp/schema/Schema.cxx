
#include "Schema.h"

#include <memory>
#include <iostream>

/******************************************************************************
 *
 * Non member related functions
 *
 ******************************************************************************/

namespace amqp::internal::schema {

std::ostream &
operator << (std::ostream & stream_, const Schema & schema_) {
    uint32_t count { 1 };
    bool first { true };

    /*
    for (auto const & type : schema_.m_types) {
        if (!first) stream_ << std::endl << std::endl; else first = false;
        stream_ << count++ << "/" << schema_.m_types.size() << ") "
                <<  type->name() << std::endl
                << *type;
    }
     */

    return stream_;
}

}

/******************************************************************************
 *
 * amqp::internal::schema::Schema
 *
 ******************************************************************************/

amqp::internal::schema::
Schema::Schema (
        OrderedTypeNotations<AMQPTypeNotation> types_
) : m_types (std::move (types_)) {
    for (auto i { m_types.begin() } ; i != m_types.end() ; ++i) {
        for (auto & j : *i) {
            std::cout << j->descriptor() << " " << j->name() << std::endl;
            m_descriptorToType.emplace(j->descriptor(), std::ref (j));
            m_typeToDescriptor.emplace(j->name(), std::ref (j));
        }
    }
}

/******************************************************************************/

const amqp::internal::schema::OrderedTypeNotations<amqp::internal::schema::AMQPTypeNotation> &
amqp::internal::schema::
Schema::types() const {
    return m_types;
}

/******************************************************************************/

amqp::internal::schema::Schema::SchemaMap::const_iterator
amqp::internal::schema::
Schema::fromType (const std::string & type_) const {
    return m_typeToDescriptor.find(type_);
}

/******************************************************************************/

amqp::internal::schema::Schema::SchemaMap::const_iterator
amqp::internal::schema::
Schema::fromDescriptor (const std::string & descriptor_) const {
    return m_descriptorToType.find (descriptor_);
}

/******************************************************************************/

