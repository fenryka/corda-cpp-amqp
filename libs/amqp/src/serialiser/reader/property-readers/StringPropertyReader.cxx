#include "StringPropertyReader.h"

#include <proton/codec.h>

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************
 *
 * class StringPropertyReader
 *
 ******************************************************************************/

std::any
amqp::internal::serialiser::reader::
StringPropertyReader::read (pn_data_t * data_) const {
    return std::any { proton::readAndNext<std::string> (data_) };
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
StringPropertyReader::readString (pn_data_t * data_) const {
    return proton::readAndNext<std::string> (data_);
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
StringPropertyReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedPair<std::string>> (
            name_,
            "\"" + proton::readAndNext<std::string> (data_) + "\"");
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
StringPropertyReader::dump (
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedSingle<std::string>> (
            "\"" + proton::readAndNext<std::string> (data_) + "\"");
}

/******************************************************************************/

