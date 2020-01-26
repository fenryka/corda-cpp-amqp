#pragma once

/******************************************************************************/

#include "RestrictedReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class MapReader : public RestrictedReader {
        private :
            sVec<uPtr<amqp::serialiser::reader::IValue>> dump_(
                    pn_data_t *,
                    const amqp::schema::ISchema &) const;

        public :
            MapReader() = default;
            ~MapReader() override = default;

            internal::schema::Restricted::RestrictedTypes restrictedType() const;

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
