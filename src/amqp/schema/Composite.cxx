#include "Composite.h"

#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Composite & clazz_) {
    stream_
        << "name       : " << clazz_.m_name << std::endl
        << "label      : " << clazz_.m_label << std::endl
        << "descriptor : " << *clazz_.m_descriptor << std::endl;

    return stream_;
}

/******************************************************************************/
