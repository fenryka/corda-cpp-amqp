#pragma once

/******************************************************************************/

#include "serialisers/reader/Reader.h"

#include "field-types/Field.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class PropertyReader : public Reader {
        private :
            using FieldPtr = uPtr<internal::schema::Field>;

        public :
            PropertyReader() = default;
            ~PropertyReader() override = default;

            std::string readString (pn_data_t *) const override = 0;

            std::any read (pn_data_t *) const override = 0;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const amqp::schema::ISchema &
            ) const override = 0;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                pn_data_t *,
                const amqp::schema::ISchema &
            ) const override = 0;
    };

}

/******************************************************************************/


