
#include "Schema.h"

#include <iostream>

/******************************************************************************
 *
 * Non member related functions
 *
 ******************************************************************************/

namespace {

    using CompositeMap = std::map<
        std::string,
        std::unique_ptr<amqp::internal::schema::AMQPTypeNotation>>;

}

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Schema & schema_) {
    uint32_t count { 0 };
    for (auto const & type : schema_.m_types) {
        stream_ << count++ << "/" << schema_.m_types.size() << ") "
                <<  type.first << std::endl
                << *type.second << std::endl << std::endl;
    }

    return stream_;
}

/******************************************************************************
 *
 * amqp::internal::schema::Schema
 *
 ******************************************************************************/

/**
 * Constructor
 *
 * @param types_ the restricted and composite types contined within the
 *               schema.
 */
amqp::internal::schema::
Schema::Schema (
    std::map<std::string, std::unique_ptr<AMQPTypeNotation>> & types_
) : m_types (std::move (types_)) {
    for (auto & t : m_types) {
        std::cout << t.second->name() << std::endl;
        std::cout << "\"" << t.second->descriptor() << "\"" << std::endl;
        m_descriptorToType[t.second->descriptor()] = t.first;
    }
}

/******************************************************************************/

const CompositeMap &
amqp::internal::schema::
Schema::types() const {
    return m_types;
}

/******************************************************************************/

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::fromType (const std::string & type_) const {
    return m_types.find (type_);
}

/******************************************************************************/

decltype (amqp::internal::schema::Schema::m_types)::const_iterator
amqp::internal::schema::
Schema::fromDescriptor (const std::string & descriptor_) const {
    const auto type = m_descriptorToType.find (descriptor_);

    return (type == m_descriptorToType.end()) ? m_types.end() : fromType (type->second);
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
