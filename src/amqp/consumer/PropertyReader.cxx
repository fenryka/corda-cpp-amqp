#include "PropertyReader.h"

#include <string>

#include <proton/codec.h>

std::string
amqp::
PropertyReader::read (pn_data_t * data_) const {
    pn_data_next (data_);
    return "Property";
}
