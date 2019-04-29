#include "Descriptor.h"

/******************************************************************************/

namespace amqp::internal::schema {

std::ostream &
operator << (std::ostream & stream_, const Descriptor & desc_) {
    stream_ << desc_.m_name;
    return stream_;
}

}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

amqp::internal::schema::
Descriptor::Descriptor (const std::string & name_)
    : m_name (name_)
{ }

/******************************************************************************/

const std::string &
amqp::internal::schema::
Descriptor::name() const {
    return m_name;
}

/******************************************************************************/

