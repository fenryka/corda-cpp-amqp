#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"

#include "corda-utils/include/types.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory;

}

/******************************************************************************/

namespace amqp::serializable {

    class Serializable {
        private :
            std::string m_fingerprint;

        public :
            Serializable() = delete;

            explicit Serializable (std::string fingerprint_)
                : m_fingerprint (std::move (fingerprint_))
            { }

            [[nodiscard]] uPtr<AMQPBlob> serialize (
                    const amqp::assembler::SerialiserFactory &) const;

            [[nodiscard]] const std::string & fingerprint() const {
                return m_fingerprint;
            }

            [[nodiscard]] virtual uPtr<amqp::serialiser::ISerialiser> build() const = 0;
    };

}
/******************************************************************************/
