#include "Envelope.h"

#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (
        std::ostream & stream_,
        const amqp::internal::schema::Envelope & e_
) {
    stream_ << *(e_.m_schema);
    return stream_;
}

/******************************************************************************/

