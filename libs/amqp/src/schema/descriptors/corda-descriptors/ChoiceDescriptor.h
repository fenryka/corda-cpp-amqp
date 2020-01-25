#pragma once

#include "descriptors/AMQPDescriptor.h"

/******************************************************************************
 *
 * Represents an enumeration
 *
 ******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class ChoiceDescriptor : public AMQPDescriptor {
        public :
            ChoiceDescriptor() = delete;

            ChoiceDescriptor (std::string, int);

            ~ChoiceDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;
    };

}

/******************************************************************************/
