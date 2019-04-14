#include "Composite.h"

#include <iomanip>
#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Composite & clazz_) {
    stream_
        << "name       : " << clazz_.m_name << std::endl
        << "label      : " << clazz_.m_label << std::endl
        << "descriptor : " << *clazz_.m_descriptor << std::endl
        << "fields     : ";

    std::cout << "LEN = " << clazz_.m_fields.size() << std::endl;
    for (auto const & i : clazz_.m_fields) stream_ << *i << std::setw (13) << " ";
    stream_ << std::setw(0);

    return stream_;
}

/******************************************************************************/
