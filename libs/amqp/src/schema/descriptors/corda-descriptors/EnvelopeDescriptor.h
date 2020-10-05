#pragma once

#include <string>

#include "amqp/src/schema/descriptors/AMQPDescriptors.h"

/******************************************************************************
 *
 * Forward Class Declarations
 *
 ******************************************************************************/

struct pn_data_t;

/******************************************************************************
 *
 * class amqp::internal::EnvelopeDescriptor
 *
 ******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class EnvelopeDescriptor final : public AMQPDescriptor {
        public :
            EnvelopeDescriptor() = delete;
            EnvelopeDescriptor (std::string, int);

            ~EnvelopeDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;

            void readRaw (
                    pn_data_t *,
                    std::stringstream &,
                    const AutoIndent &) const override;

            void readAvro (
                pn_data_t *,
                std::stringstream &,
                const AutoIndent &) const override;

            [[nodiscard]] static pn_data_t * makeProton (
                    pn_data_t *,
                    pn_data_t *);
    };

}

/******************************************************************************/
