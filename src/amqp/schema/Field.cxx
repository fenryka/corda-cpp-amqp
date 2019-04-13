#include "Field.h"

#include <sstream>
#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Field & field_) {
    std::stringstream ss;
    for (auto &i: field_.m_requires) { ss << i; }

    stream_ << field_.m_name << " : " << field_.m_type << ss.str() << std::endl;

    return stream_;
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
Field::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
Field::type() const {
    return m_type;
}

/******************************************************************************/

bool
amqp::internal::schema::
Field::primitive() const {
    return (m_type == "string" ||
            m_type == "long" ||
            m_type == "boolean" ||
            m_type == "int" ||
            m_type == "double");
}

/******************************************************************************/
