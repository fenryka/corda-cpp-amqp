#pragma once

#include "descriptors/AMQPDescriptor.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class CompositeDescriptor : public AMQPDescriptor {
        public :
            CompositeDescriptor() = delete;
            CompositeDescriptor (std::string, int);

            ~CompositeDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;

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
