#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/ModifiableAMQPBlob.h"
#include "amqp/include/serialiser/ISerialiser.h"

#include "corda-utils/include/types.h"

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

        protected :
            virtual void serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &) const = 0;

        public :
            Serializable() = delete;

            virtual void serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob &) const;

            [[nodiscard]]
            virtual uPtr<AMQPBlob> serialise (
                const amqp::assembler::SerialiserFactory & sf_
            ) const;

            explicit Serializable (
                std::string name_,
                std::string fingerprint_);


            [[nodiscard]] const std::string & name() const;

            [[nodiscard]] const std::string & fingerprint() const;
    };

}

/******************************************************************************/
