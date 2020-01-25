#pragma once

/******************************************************************************/

#include "RestrictedReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class ArrayReader : public RestrictedReader {
        private :
            // How to read the underlying types
            std::weak_ptr<Reader> m_reader;

            std::list<uPtr<amqp::serialiser::reader::IValue>> dump_(
                pn_data_t *,
                const amqp::schema::ISchema &) const;

            /**
             * cope with the fact Java can box primitives
             */
            std::string m_primType;

        public :
            ArrayReader (std::string, std::weak_ptr<Reader>);

            ~ArrayReader() final = default;

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
