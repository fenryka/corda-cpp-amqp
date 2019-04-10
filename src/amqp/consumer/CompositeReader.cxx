#include "CompositeReader.h"

#include <string>

#include <proton/codec.h>

std::string
amqp::
CompositeReader::read (pn_data_t * data_) const {
    pn_data_next (data_);
    return "Composite";
}
