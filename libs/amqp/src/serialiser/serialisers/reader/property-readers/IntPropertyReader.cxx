#include "IntPropertyReader.h"

#include <any>
#include <string>
#include <proton/codec.h>

#include "proton-wrapper/include/proton_wrapper.h"
#include "serialiser/reader/IReader.h"

/******************************************************************************
 *
 * IntPropertyReader
 *
 ******************************************************************************/

std::any
amqp::internal::serialiser::reader::
IntPropertyReader::read (pn_data_t * data_) const {
    return std::any { proton::readAndNext<int> (data_, __FILE__, __LINE__) };
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
IntPropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<int> (data_, __FILE__, __LINE__));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
IntPropertyReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    DBG ("IntPropertyReader::dump - " << name_ << std::endl); // NOLINT
    return std::make_unique<TypedPair<std::string>> (
            name_,
            std::to_string (proton::readAndNext<int> (data_, __FILE__, __LINE__)));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
IntPropertyReader::dump (
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    DBG ("IntPropertyReader::dump - no-name" << std::endl); // NOLINT
    return std::make_unique<TypedSingle<std::string>> (
            std::to_string (proton::readAndNext<int> (data_, __FILE__, __LINE__)));
}

/******************************************************************************/

