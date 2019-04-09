
#include "Schema.h"

#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Schema & schema_) {
    for (auto const & type : schema_.m_types) {
        stream_ << type.first << std::endl;
        stream_ << *type.second << std::endl;
    }

    return stream_;
}

/******************************************************************************/
