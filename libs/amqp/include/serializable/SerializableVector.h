#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serialiser/ISerialiser.h"
#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/include/ModifiableAMQPBlob.h"

#include "corda-utils/include/debug.h"

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory;

}

/******************************************************************************/

namespace amqp::serializable {

    template<typename T, typename A = std::allocator<T>>
    class SerializableVector final : public std::vector<T, A>, public Serializable {
        private :
            /**
             *
             */
            void _serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "::" << name() << std::endl); // NOLINT

                sf_.startRestricted (*this, blob_);

                for (const auto & i: *this) {
                    sf_.writeSingle<T> (i, *this, blob_);
                }
            }

        protected :
            void serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &
            ) const override {
                DBG (__FUNCTION__ << std::endl);
            }

        public :
            SerializableVector() = delete;

            SerializableVector(
                const std::string & fingerprint_
            ) : std::vector<T>()
              , Serializable (javaTypeName<std::vector<T, A>>(), fingerprint_)
            { }

            SerializableVector(
                const std::string& name_,
                const std::string& fingerprint_,
                std::initializer_list<T> l_
            ) : std::vector<T>(l_)
              , Serializable (javaTypeName<std::vector<T, A>>(), fingerprint_)
            { }

            SerializableVector(
                const std::string & fingerprint_,
                std::vector<T> && v_
            ) : std::vector<T>(v_)
              , Serializable (javaTypeName<std::vector<T, A>>(), fingerprint_)
            { }

            void serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                return _serialise (sf_, blob_);
            }

            [[nodiscard]]
            uPtr<AMQPBlob> serialise (
                const amqp::assembler::SerialiserFactory & sf_
            ) const override {
                auto blob = sf_.blob();
                _serialise (sf_, *blob);
                return blob->toBlob();
            }
    };
}


/******************************************************************************/

/**
 * Our type library needs a little help with our custom vector type
 */
template<typename T, typename A>
struct [[maybe_unused]] is_std_vector<amqp::serializable::SerializableVector<T, A>> : std::true_type {
    static std::string fun () {
        return "java.util.List<" + javaTypeName<T> () + ">";
    }
};

/******************************************************************************/
