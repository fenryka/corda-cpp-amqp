#include "PropertyReader.h"

#include <map>
#include <string>
#include <functional>

#include <proton/codec.h>

#include "proton/proton_wrapper.h"

/******************************************************************************/

namespace {

    std::map<std::string, std::shared_ptr<amqp::PropertyReader>(*)() > propertyMap = {
        {
            "int", []() -> std::shared_ptr<amqp::PropertyReader> {
                return std::make_shared<amqp::IntPropertyReader> (
                        amqp::IntPropertyReader());
            }
        },
        {
            "string", []() -> std::shared_ptr<amqp::PropertyReader> {
                return std::make_shared<amqp::StringPropertyReader> (
                        amqp::StringPropertyReader());
            }
        },
        {
            "boolean", []() -> std::shared_ptr<amqp::PropertyReader> {
                return std::make_shared<amqp::BoolPropertyReader> (
                        amqp::BoolPropertyReader());
            }
        },
        {
            "long", []() -> std::shared_ptr<amqp::PropertyReader> {
                return std::make_shared<amqp::LongPropertyReader> (
                        amqp::LongPropertyReader());
            }
        },
        {
            "double", []() -> std::shared_ptr<amqp::PropertyReader> {
                return std::make_shared<amqp::DoublePropertyReader> (
                        amqp::DoublePropertyReader());
            }
        }
    };

}

/******************************************************************************/

/**
 * Static factory method
 */
std::shared_ptr<amqp::PropertyReader>
amqp::
PropertyReader::make (const FieldPtr & field_) {
    return propertyMap[field_->type()]();
}

/******************************************************************************
 *
 * StringPropertyReader
 *
 ******************************************************************************/

std::any
amqp::
StringPropertyReader::read (pn_data_t * data_) const {
    return std::any ("hello");
}

/******************************************************************************/

std::string
amqp::
StringPropertyReader::readString (pn_data_t * data_) const {
    return proton::readAndNext<std::string> (data_);
}

/******************************************************************************/

std::string
amqp::
StringPropertyReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    return "hello";
}

/******************************************************************************
 *
 * IntPropertyReader
 *
 ******************************************************************************/

std::any
amqp::
IntPropertyReader::read (pn_data_t * data_) const {
    return std::any (1);
}

/******************************************************************************/

std::string
amqp::
IntPropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<int> (data_));
}

/******************************************************************************/

std::string
amqp::
IntPropertyReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    return "hello";
}

/******************************************************************************
 *
 * BoolPropertyReader
 *
 ******************************************************************************/

std::any
amqp::
BoolPropertyReader::read (pn_data_t * data_) const {
    return std::any (true);
}

/******************************************************************************/

std::string
amqp::
BoolPropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<bool> (data_));
}

/******************************************************************************/

std::string
amqp::
BoolPropertyReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    return "hello";
}

/******************************************************************************
 *
 * LongPropertyReader
 *
 ******************************************************************************/

std::any
amqp::
LongPropertyReader::read (pn_data_t * data_) const {
    return std::any (10L);
}

/******************************************************************************/

std::string
amqp::
LongPropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<long> (data_));
}

/******************************************************************************/

std::string
amqp::
LongPropertyReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    return "hello";
}

/******************************************************************************
 *
 * DoublePropertyReader
 *
 ******************************************************************************/

std::any
amqp::
DoublePropertyReader::read (pn_data_t * data_) const {
    return std::any (10.0);
}

/******************************************************************************/

std::string
amqp::
DoublePropertyReader::readString (pn_data_t * data_) const {
    return std::to_string (proton::readAndNext<double> (data_));
}

/******************************************************************************/

std::string
amqp::
DoublePropertyReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    return "hello";
}

/******************************************************************************/

