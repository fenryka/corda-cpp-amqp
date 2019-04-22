#include <iostream>
#include "RestrictedReader.h"

/******************************************************************************/

const std::string amqp::RestrictedReader::m_name { // NOLINT
    "Restricted Reader"
};

/******************************************************************************/

std::any
amqp::
RestrictedReader::read(pn_data_t *) const {
    return std::any(1);
}

/******************************************************************************/

std::string
amqp::
RestrictedReader::readString(pn_data_t * data_) const {
    return "hello";
}

/******************************************************************************/

std::unique_ptr<amqp::Pair>
amqp::
RestrictedReader::dump (
    const std::string &,
    pn_data_t *,
    const std::unique_ptr<internal::schema::Schema> &
) const {
    std::cout << "Dump rest" << std::endl;
    return nullptr;
}

/******************************************************************************/

const std::string &
amqp::
RestrictedReader::name() const {
    return m_name;
}

/******************************************************************************/
