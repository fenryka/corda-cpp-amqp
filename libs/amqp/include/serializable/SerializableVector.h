#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serialiser/ISerialiser.h"
#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/serializable/RestrictedSerializable.h"
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
    class SerializableVector final : public std::vector<T, A>, public RestrictedSerializable {
        private :
            friend class amqp::assembler::SerialiserFactory;

            /**
             *
             */
            void _serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "::" << name() << std::endl); // NOLINT

                amqp::internal::serializable::AutoRestrictedWrite ar (*this, blob_);

                for (const auto & i: *this) {
                    sf_.writeSingle<T> (i, *this, blob_);
                }
            }

            /**
             *
             * @param sf_
             * @param blob_
             * @return
             */
            [[maybe_unused]]
            static std::vector<std::any>
            deserialiseImpl (
                const amqp::assembler::SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {


                while (true) {
                    sf_.readSingle<T> (blob_);
                }
            }

        protected :
            /**
             *
             */
            void serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &
            ) const override {
                DBG (__FUNCTION__ << std::endl); // NOLINT
            }

        public :
            SerializableVector() = delete;

            explicit SerializableVector(
                const std::string & fingerprint_
            ) : std::vector<T>()
              , RestrictedSerializable (javaTypeName<std::vector<T, A>>(), fingerprint_, "list")
            { }

            SerializableVector(
                const std::string& fingerprint_,
                std::initializer_list<T> l_
            ) : std::vector<T>(l_)
              , RestrictedSerializable (javaTypeName<std::vector<T, A>>(), fingerprint_, "list")
            { }

            SerializableVector(
                const std::string & fingerprint_,
                std::vector<T> && v_
            ) : std::vector<T>(v_)
              , RestrictedSerializable (javaTypeName<std::vector<T, A>>(), fingerprint_, "list")
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
