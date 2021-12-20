#include "IntPropertyReader.h"

#include <any>
#include <string>

#include "include/proton_wrapper.h"

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
#if defined (AMQP_DEBUG) && (AMQP_DEBUG >= 1)
    DBG ("FUCK 1" << std::endl);
    //auto v = proton::readAndNext<int32_t> (data_, __FILE__, __LINE__);
    auto v = proton::readAndNext<int> (data_, __FILE__, __LINE__);

    DBG ("    -> " << v << std::endl);

    return std::make_unique<TypedPair<std::string>> (
            name_, std::to_string (v));
#else
    DBG ("FUCK 2" << std::endl);
    return std::make_unique<TypedPair<std::string>> (
            name_,
            std::to_string (proton::readAndNext<int32_t> (data_, __FILE__, __LINE__)));
#endif
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

