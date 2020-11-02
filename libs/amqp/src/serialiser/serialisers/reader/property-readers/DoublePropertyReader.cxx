#include "DoublePropertyReader.h"

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************
 *
 * DoublePropertyReader
 *
 ******************************************************************************/

std::any
amqp::internal::serialiser::reader::
DoublePropertyReader::read (pn_data_t * data_) const {
    return std::any { proton::readAndNext<double> (data_, __FILE__, __LINE__) };
}

/******************************************************************************/

std::string
amqp::internal::serialiser::reader::
DoublePropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<double> (data_, __FILE__, __LINE__));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
DoublePropertyReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedPair<std::string>> (
            name_,
            std::to_string (proton::readAndNext<double> (data_, __FILE__, __LINE__)));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
DoublePropertyReader::dump (
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_) const
{
    return std::make_unique<TypedSingle<std::string>> (
            std::to_string (proton::readAndNext<double> (data_, __FILE__, __LINE__)));
}

/******************************************************************************/

