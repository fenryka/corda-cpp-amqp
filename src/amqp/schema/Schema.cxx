
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
    /*
    std::transform (m_types.begin(), m_types.end(), std::inserter( m_descriptorToType, m_descriptorToType.begin() ),
            []( uPtr<AMQPTypeNotation> ){ return std::pair<const char, int>( c, 0 ); } );
            */

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

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::fromType (const std::string & type_) const {
//    return m
//    return m_types.find (type_);
    return std::end (m_types);
}

/******************************************************************************/

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::fromDescriptor (const std::string & descriptor_) const {
    const auto type = m_descriptorToType.find (descriptor_);

    return std::end (m_types);
//    return (type == m_descriptorToType.end()) ? m_types.end() : fromType (type->second);
}

/******************************************************************************/

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::end() const {
    return m_types.cend();
}

/******************************************************************************/

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::begin() const {
    return m_types.cbegin();
}

/******************************************************************************/
