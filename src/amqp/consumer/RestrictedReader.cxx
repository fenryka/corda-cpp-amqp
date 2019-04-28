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

std::unique_ptr<amqp::Pair>
amqp::
RestrictedReader::dump (
    const std::string &,
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> &
) const {
    std::cout << "Dump rest" << std::endl;

    std::cout << "D1 " << data_ << std::endl;

    {
        proton::auto_enter_and_next ae (data_);
        std::cout << data_ << std::endl;

        pn_data_next (data_);
        std::cout << data_ << std::endl;

        {
            proton::auto_list_enter ale (data_);
            std::cout << "elements: " << ale.elements() << std::endl;

            std::cout << "l1: " << data_ << std::endl;

            pn_data_next (data_);

            std::cout << "l2: " << data_ << std::endl;

            {
                proton::auto_enter ae (data_);
                std::cout << "  * " << data_ << std::endl;

                pn_data_next(data_);
                std::cout << "  * " << data_ << std::endl;


                {
                    proton::auto_list_enter ale(data_);
                    std::cout << "    elements: " << ale.elements() << std::endl;

                    std::cout << "      #" << data_ << std::endl;
                    pn_data_next(data_);
                    std::cout << "      #" << data_ << std::endl;
                    pn_data_next(data_);
                    std::cout << "      #" << data_ << std::endl;
                    pn_data_next(data_);
                    std::cout << "      #" << data_ << std::endl;
                    pn_data_next(data_);
                    std::cout << "      #" << data_ << std::endl;
                    pn_data_next(data_);
                    std::cout << "      #" << data_ << std::endl;
                }
            }
        }
    }

    std::cout << "D2 " << data_ << std::endl;

    std::cout << amqp::describedToString(static_cast<uint64_t>(pn_data_get_long(data_))) << std::endl;


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

