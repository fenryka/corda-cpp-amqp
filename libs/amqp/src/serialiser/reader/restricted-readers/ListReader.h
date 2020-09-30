#pragma once

/******************************************************************************/

#include <amqp/include/serialiser/ISerialiser.h>
#include "RestrictedReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class ListReader : public RestrictedReader {
        private :
            std::list<uPtr<amqp::serialiser::reader::IValue>> dump_(
                pn_data_t *,
                const amqp::schema::ISchema &) const;

        public :
            ListReader() = default;
            ~ListReader() override = default;

            [[nodiscard]] internal::schema::Restricted::RestrictedTypes restrictedType() const;

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
