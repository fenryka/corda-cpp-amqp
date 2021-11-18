#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/ModifiableAMQPBlob.h"
#include "amqp/include/serialiser/ISerialiser.h"

#include "corda-utils/include/types.h"

#include "amqp/include/assembler/SerialiserFactory.h"

#include "corda-utils/include/debug.h"

#include <any>
#include <list>

/******************************************************************************/

#define FINGERPRINT_NOT_SET "FINGERPRINT_NOT_SET"
#define JAVATYPE_NOT_SET "JAVATYPE_NOT_SET"

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory;

}

/******************************************************************************/


namespace amqp::serializable {

    template<typename T>
    struct Fingerprint {
        static const std::string val;

        [[nodiscard]] const std::string & _fingerprint() const {
#if defined (AMQP_DEBUG) && AMQP_DEBUG > 0
            if (val == FINGERPRINT_NOT_SET) {
                throw std::runtime_error("Fingerprint not set - " + javaTypeName<T>());
            }
#endif
            return val;
        }
    };

    template<typename T> const std::string Fingerprint<T>::val = FINGERPRINT_NOT_SET; // NOLINT

    template<typename T>
    struct JavaType {
        static const std::string val;
    };

    template<typename T> const std::string JavaType<T>::val = JAVATYPE_NOT_SET; // NOLINT

}

/******************************************************************************/

namespace amqp::serializable {

    class SerializableBase {
        private :
            const std::string m_name;

        protected :
            virtual void
            serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &) const = 0;

        public :
            [[nodiscard]] const std::string & name() const;

            explicit SerializableBase (std::string name_);

            [[nodiscard]]
            virtual uPtr<AMQPBlob> serialise (
                const amqp::assembler::SerialiserFactory & sf_
            ) const;

            virtual void serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob &) const;

            [[nodiscard]] virtual const std::string & fingerprint() const = 0;
            [[nodiscard]] virtual const std::string & javaType() const = 0;
    };

    template <typename FINGERPRINT>
    class Serializable : public SerializableBase, private Fingerprint<FINGERPRINT> {
        public :
            Serializable() = delete;

            explicit Serializable (const std::string & name_)
                : SerializableBase (name_)
            {}

           [[nodiscard]] const std::string & fingerprint() const override {
                return this->_fingerprint();
            }

            [[nodiscard]] const std::string & javaType() const override {
                throw std::runtime_error("For f sake");
            }
    };

}

/******************************************************************************/
