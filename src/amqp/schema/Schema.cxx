
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

    for (auto const & type : schema_.m_types) {
        if (!first) stream_ << std::endl << std::endl; else first = false;
        stream_ << count++ << "/" << schema_.m_types.size() << ") "
                <<  type->name() << std::endl
                << *type;
    }

    return stream_;
}

}

/******************************************************************************
 *
 * amqp::internal::schema::Schema
 *
 ******************************************************************************/

amqp::internal::schema::SetSort
amqp::internal::schema::Schema::setSorter =
        [](const uPtr<amqp::internal::schema::AMQPTypeNotation> &lhs,
           const uPtr<amqp::internal::schema::AMQPTypeNotation> &rhs
        ) {
            return lhs->lt(rhs);
        };

/******************************************************************************/

amqp::internal::schema::
Schema::Schema (
    std::set<uPtr<AMQPTypeNotation>, amqp::internal::schema::SetSort > types_
) : m_types (std::move (types_)) {
    for (const auto & t : m_types) {
        m_descriptorToType.emplace(t->descriptor(), std::ref (t));
        m_typeToDescriptor.emplace(t->name(), std::ref (t));
    }
}

/******************************************************************************/

const amqp::internal::schema::Schema::SchemaSet &
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

amqp::internal::schema::Schema::SchemaSet::const_iterator
amqp::internal::schema::
Schema::end() const {
    return m_types.cend();
}

/******************************************************************************/

amqp::internal::schema::Schema::SchemaSet::const_iterator
amqp::internal::schema::
Schema::begin() const {
    return m_types.cbegin();
}

/******************************************************************************/
