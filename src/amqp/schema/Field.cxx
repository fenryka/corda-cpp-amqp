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

