#include "Composite.h"

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
