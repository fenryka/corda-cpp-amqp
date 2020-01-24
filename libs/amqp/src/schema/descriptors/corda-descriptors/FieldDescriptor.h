#pragma once

/******************************************************************************/

#include "proton/codec.h"

#include "amqp/src/schema/AMQPDescribed.h"
#include "descriptors/AMQPDescriptor.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class FieldDescriptor : public AMQPDescriptor {
        public :
            FieldDescriptor() = delete;
            FieldDescriptor (std::string, int);

            ~FieldDescriptor() final = default;

            std::unique_ptr<AMQPDescribed> build (pn_data_t *) const override;

            void readRaw (
                pn_data_t *,
                std::stringstream &,
                const AutoIndent &) const override;

            void readAvro (
                pn_data_t *,
                std::stringstream &,
                const AutoIndent &) const override;
    };

}

/******************************************************************************/
