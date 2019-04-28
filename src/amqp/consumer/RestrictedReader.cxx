#include <iostream>
#include <amqp/descriptors/AMQPDescriptorRegistory.h>
#include "RestrictedReader.h"

#include "proton/proton_wrapper.h"

/******************************************************************************/

const std::string amqp::RestrictedReader::m_name { // NOLINT
    "Restricted Reader"
};

/******************************************************************************/

std::any
amqp::
RestrictedReader::read(pn_data_t *) const {
    return std::any(1);
}

/******************************************************************************/

std::string
amqp::
RestrictedReader::readString(pn_data_t * data_) const {
    return "hello";
}

/******************************************************************************/

std::unique_ptr<amqp::Value>
amqp::
ListReader::dump (
    const std::string &,
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_
) const {
    std::cout << "List Dump" << std::endl;
    proton::is_described (data_);
    std::cout << data_ << std::endl;

    std::list<std::unique_ptr<amqp::Value>> read;

    {
        proton::auto_enter ae (data_);
        auto it = schema_->fromDescriptor(proton::readAndNext<std::string>(data_));
        std::cout << (*it).first << std::endl;

        {
            proton::auto_list_enter ale (data_, true);

            for (int i { 0 } ; i < ale.elements() ; ++i) {
                auto a = m_reader.lock()->dump("a", data_, schema_);
//                read.emplace_back(a);
            }

            std::cout << "done" << std::endl;
        }
    }

    std::cout << data_ << std::endl;
    pn_data_next(data_);
    return nullptr;
}

/******************************************************************************/

const std::string &
amqp::
RestrictedReader::name() const {
    return m_name;
}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

amqp::internal::schema::Restricted::RestrictedTypes
amqp::
ListReader::type() const {
    return internal::schema::Restricted::RestrictedTypes::List;
}

/******************************************************************************/

