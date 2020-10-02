#pragma once

/******************************************************************************/

#include "amqp/include/ModifiableAMQPBlob.h"
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
            std::string m_namespace;

        protected :
            [[nodiscard]] virtual uPtr<AMQPBlob> serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                uPtr<ModifiableAMQPBlob>) const = 0;

        public :
            Serializable() = delete;

            explicit Serializable (
                    std::string fingerprint_,
                    std::string namespace_
            ) : m_fingerprint (std::move (fingerprint_))
              , m_namespace (std::move (namespace_)
            ) {

            }

            [[nodiscard]] uPtr<AMQPBlob> serialise (
                    const amqp::assembler::SerialiserFactory & sf_
            ) const {
                return serialiseImpl(sf_, std::make_unique<amqp::ModifiableAMQPBlob>());
            }

            [[nodiscard]] const std::string & fingerprint() const {
                    return m_fingerprint;
            }

            [[nodiscard]] virtual uPtr<amqp::serialiser::ISerialiser> build (
                    amqp::assembler::SerialiserFactory &) const = 0;
    };

}
/******************************************************************************/
