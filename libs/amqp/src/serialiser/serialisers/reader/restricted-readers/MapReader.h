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

            [[maybe_unused]] [[nodiscard]] static internal::schema::Restricted::RestrictedTypes restrictedType() ;

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
