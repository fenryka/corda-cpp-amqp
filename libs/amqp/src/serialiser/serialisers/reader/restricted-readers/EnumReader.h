#pragma once

#include "RestrictedReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class EnumReader : public RestrictedReader {
        public :
            EnumReader() = default;
            ~EnumReader() override = default;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const amqp::schema::ISchema &) const override;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                pn_data_t *,
                const amqp::schema::ISchema &) const override;
    };

}

/******************************************************************************/
