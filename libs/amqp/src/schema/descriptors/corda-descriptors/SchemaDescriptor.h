#pragma once

#include "descriptors/AMQPDescriptor.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class SchemaDescriptor : public AMQPDescriptor {
    public :
        SchemaDescriptor() = delete;
        SchemaDescriptor (std::string, int);
        ~SchemaDescriptor() final = default;

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
