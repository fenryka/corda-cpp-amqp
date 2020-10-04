#pragma once

/******************************************************************************/

#include "proton/codec.h"

#include "descriptors/AMQPDescriptor.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class FieldDescriptor final : public AMQPDescriptor {
        public :
            FieldDescriptor() = delete;
            FieldDescriptor (std::string, int);

            ~FieldDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;

            void readRaw (
                pn_data_t *,
                std::stringstream &,
                const AutoIndent &) const override;

            void readAvro (
                pn_data_t *,
                std::stringstream &,
                const AutoIndent &) const override;

            [[nodiscard]] static pn_data_t * makeProton(
                    const std::string &,
                    const std::string &,
                    const std::vector<std::string> &,
                    const std::string &,
                    const std::string &,
                    bool,
                    bool
            );
    };

}

/******************************************************************************/
