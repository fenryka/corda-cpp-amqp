#include "RestrictedReader.h"

#include <iostream>

#include "proton-wrapper/include/proton_wrapper.h"

#include "serialiser/reader/IReader.h"
#include "Reader.h"

/******************************************************************************/

amqp::internal::serialiser::reader::
RestrictedReader::RestrictedReader (std::string type_)
    : m_type (std::move (type_))
{ }

/******************************************************************************/

const std::string
amqp::internal::serialiser::reader::
RestrictedReader::m_name { // NOLINT
    "Restricted Reader"
};

/******************************************************************************/

std::any
amqp::internal::serialiser::reader::
RestrictedReader::read (pn_data_t *) const {
    return std::any(1);
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
RestrictedReader::readString (pn_data_t * data_) const {
    return "hello";
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
RestrictedReader::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::internal::serialiser::reader::
RestrictedReader::type() const {
    return m_type;
}

/******************************************************************************/
