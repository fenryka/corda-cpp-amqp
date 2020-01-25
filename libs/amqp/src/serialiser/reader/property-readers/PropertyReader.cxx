#include "PropertyReader.h"

#include "property-readers/IntPropertyReader.h"
#include "property-readers/BoolPropertyReader.h"
#include "property-readers/LongPropertyReader.h"
#include "property-readers/StringPropertyReader.h"
#include "property-readers/DoublePropertyReader.h"

#include <map>
#include <string>
#include <iostream>
#include <functional>

#include <proton/codec.h>

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************/

namespace {

    using namespace amqp::internal::serialiser::reader;

    std::map<
            std::string,
            std::shared_ptr<amqp::internal::serialiser::reader::PropertyReader>(*)()
    > propertyMap = { // NOLINT
        {
            "int", []() -> std::shared_ptr<PropertyReader> {
                return std::make_shared<IntPropertyReader> ();
            }
        },
        {
            "string", []() -> std::shared_ptr<PropertyReader> {
                return std::make_shared<StringPropertyReader> ();
            }
        },
        {
            "boolean", []() -> std::shared_ptr<PropertyReader> {
                return std::make_shared<BoolPropertyReader> ();
            }
        },
        {
            "long", []() -> std::shared_ptr<PropertyReader> {
                return std::make_shared<LongPropertyReader> ();
            }
        },
        {
            "double", []() -> std::shared_ptr<PropertyReader> {
                return std::make_shared<DoublePropertyReader> ();
            }
        }
    };

}

/******************************************************************************
 *
 * Static methods
 *
 ******************************************************************************/

std::shared_ptr<amqp::internal::serialiser::reader::PropertyReader>
amqp::internal::serialiser::reader::
PropertyReader::make (const FieldPtr & field_) {
    return propertyMap[field_->type()]();
}

/******************************************************************************/

std::shared_ptr<amqp::internal::serialiser::reader::PropertyReader>
amqp::internal::serialiser::reader::
PropertyReader::make (const std::string & type_) {
    return propertyMap[type_]();
}

/******************************************************************************/

std::shared_ptr<amqp::internal::serialiser::reader::PropertyReader>
amqp::internal::serialiser::reader::
PropertyReader::make (const internal::schema::Field & field_) {
    return propertyMap[field_.type()]();
}

/******************************************************************************/
