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
                    std::string namespace_);

            [[nodiscard]] uPtr<AMQPBlob> serialise (
                    const amqp::assembler::SerialiserFactory & sf_
            ) const;

            [[nodiscard]] const std::string & fingerprint() const;

            [[nodiscard]] const std::string & javaNamespace() const;

            [[nodiscard]] virtual uPtr<amqp::serialiser::ISerialiser> build (
                    amqp::assembler::SerialiserFactory &) const = 0;
    };

}
/******************************************************************************/
