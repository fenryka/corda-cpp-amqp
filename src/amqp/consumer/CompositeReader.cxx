#include "CompositeReader.h"

#include <string>
#include <iostream>

#include <proton/codec.h>

#include "proton/proton_wrapper.h"

/******************************************************************************/

std::any
amqp::
CompositeReader::read (pn_data_t * data_) const {
}

/******************************************************************************/

std::string
amqp::
CompositeReader::readString (pn_data_t * data_) const {
    std::cout << "READ" << std::endl;
    pn_data_next (data_);
    return "Composite";
}

/******************************************************************************/

std::string
amqp::
CompositeReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    std::cout << "DUMP" << std::endl;

    proton::is_described (data_);
    {
        proton::auto_enter ae (data_);
        std::cout << data_ << std::endl;
        auto it = schema_->fromDescriptor(proton::get_symbol<std::string>(data_));
        std::cout << (*it).second->name() << std::endl;
    }


    return "hello";
}

/******************************************************************************/

