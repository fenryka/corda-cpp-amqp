#include "Descriptor.h"

/******************************************************************************/

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

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Descriptor & desc_) {
    stream_ << desc_.m_name;
    return stream_;
}

/******************************************************************************/
