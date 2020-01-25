#pragma once

/******************************************************************************/

#include "descriptors/AMQPDescriptor.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class ObjectDescriptor : public AMQPDescriptor {
    public :
        ObjectDescriptor() = delete;

        ObjectDescriptor (std::string, int);

        ~ObjectDescriptor() final = default;

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
