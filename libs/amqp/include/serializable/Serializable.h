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
            std::string m_name;
            std::string m_fingerprint;
            std::string m_namespace;

        protected :
            virtual void serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &) const = 0;

        public :
            Serializable() = delete;

        void serialise (
            const amqp::assembler::SerialiserFactory & sf_,
            ModifiableAMQPBlob &) const;

        explicit Serializable (
                std::string name_,
                std::string fingerprint_,
                std::string namespace_);

        [[nodiscard]] uPtr<AMQPBlob> serialise (
            const amqp::assembler::SerialiserFactory & sf_
        ) const;

        [[nodiscard]] const std::string & name() const;

        [[nodiscard]] const std::string & fingerprint() const;

        [[nodiscard]] const std::string & javaNamespace() const;
    };

}
/******************************************************************************/
