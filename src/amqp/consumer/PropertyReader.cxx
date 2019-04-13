#include "PropertyReader.h"


#include <map>
#include <string>
#include <functional>

#include <proton/codec.h>

/******************************************************************************/

namespace {

    std::map<std::string, std::unique_ptr<amqp::PropertyReader>(*)() > propertyMap = {
        {
            "int", []() -> std::unique_ptr<amqp::PropertyReader> {
                return std::make_unique<amqp::IntPropertyReader> (
                        amqp::IntPropertyReader());
            }
        },
        {
            "string", []() -> std::unique_ptr<amqp::PropertyReader> {
                return std::make_unique<amqp::StringPropertyReader> (
                        amqp::StringPropertyReader());
            }
        }
    };

}

/******************************************************************************/

std::unique_ptr<amqp::PropertyReader>
amqp::
PropertyReader::make (const FieldPtr & field_) {
    return std::unique_ptr<amqp::PropertyReader> (nullptr);
}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

std::string
amqp::
StringPropertyReader::read (pn_data_t * data_) const {
    return "String";
}

/******************************************************************************/

std::string
amqp::
IntPropertyReader::read (pn_data_t * data_) const {
    return "Iny";
}

/******************************************************************************/
