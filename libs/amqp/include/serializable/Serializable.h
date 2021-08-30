#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/ModifiableAMQPBlob.h"
#include "amqp/include/serialiser/ISerialiser.h"

#include "corda-utils/include/types.h"

#include <any>
#include <list>


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
            virtual void
            serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &) const = 0;

        /*
            [[nodiscard]]
            virtual std::list<std::any>
            deserialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                const AMQPBlob &) const = 0;

         */
        public :
            Serializable() = delete;

            virtual void serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob &) const;

            static void startComposite (
                const amqp::assembler::SerialiserFactory & sf_,
                const AMQPBlob &);

            [[nodiscard]]
            virtual uPtr<AMQPBlob> serialise (
                const amqp::assembler::SerialiserFactory & sf_
            ) const;

            /*
            std::list<std::any>
            deserialise (
                const amqp::assembler::SerialiserFactory &,
                const amqp::AMQPBlob &) const;
            */

            explicit Serializable (
                std::string name_,
                std::string fingerprint_);

            [[nodiscard]] const std::string & name() const;
            [[nodiscard]] const std::string & fingerprint() const;
    };

}

/******************************************************************************/
