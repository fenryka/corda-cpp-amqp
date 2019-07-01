#include "Composite.h"
#include "amqp/schema/restricted-types/Restricted.h"

#include <iomanip>
#include <iostream>

/******************************************************************************/

namespace amqp::internal::schema {

    std::ostream &
    operator << (std::ostream & stream_, const Composite & clazz_) {
        stream_
            << "name       : " << clazz_.name() << std::endl
            << "label      : " << clazz_.m_label << std::endl
            << "descriptor : " << clazz_.descriptor() << std::endl
            << "fields     : ";

        for (auto const & i : clazz_.m_fields) stream_ << *i << std::setw (13) << " ";
        stream_ << std::setw(0);

        return stream_;
    }

}

/******************************************************************************
 *
 * amqp::internal::schema::Composite
 *
 ******************************************************************************/

amqp::internal::schema::
Composite::Composite (
        const std::string & name_,
        const std::string & label_,
        const std::list<std::string> & provides_,
        std::unique_ptr<Descriptor> & descriptor_,
        std::vector<std::unique_ptr<Field>> & fields_
) : AMQPTypeNotation (name_, descriptor_)
  , m_label (label_)
  , m_provides (provides_)
  , m_fields (std::move (fields_))
{ }

/******************************************************************************/

const std::vector<std::unique_ptr<amqp::internal::schema::Field>> &
amqp::internal::schema::
Composite::fields() const {
    return m_fields;
}

/******************************************************************************/

amqp::internal::schema::AMQPTypeNotation::Type
amqp::internal::schema::
Composite::type() const {
    return AMQPTypeNotation::Type::Composite;
}

/******************************************************************************/

/**
 * Use a visitor style pattern to work out weather two types, composite or
 * restricted, are "less than" one or not. In this case we define being
 * "less than" not having a type that the other depends on. This will
 * eventually give us a set ordered in such a way we can simply create
 * each element in turn
 *
 * @param rhs
 * @return
 */
bool
amqp::internal::schema::
Composite::lt (const uPtr<AMQPTypeNotation> & rhs) const {
    return rhs->gte(*this);
}

/******************************************************************************/

bool
amqp::internal::schema::
Composite::gte (const amqp::internal::schema::Restricted & lhs_) const {
    std::cout << "composite gte rest" << std::endl;

    std::cout << "===" << std::endl;
    for (auto const & i : m_fields) std::cout << (*i).name() << std::endl;
    std::cout << "--" << std::endl;
    for (auto const & i : lhs_) std::cout << i << std::endl;
    std::cout << "===" << std::endl;

    return true;
}

/*********************************************************o*********************/

bool
amqp::internal::schema::
Composite::gte (const amqp::internal::schema::Composite & lhs_) const {

    for (auto const & field : lhs_) {
        if (field->type()  == name()) return false;
    }


    return true;
}

/******************************************************************************/
