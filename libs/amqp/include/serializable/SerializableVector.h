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

        protected :
            void serialiseImpl (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                DBG (__FUNCTION__ << std::endl);
            }

            typedef std::true_type isVector;

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

            template<typename U>
            void _memberSerialiser (
                const U & m,
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "NOT Serializable" << std::endl);
            }

            template<>
            [[maybe_unused]]
            void _memberSerialiser (
                const Serializable & m,
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "Serializable" << std::endl);
                m.serialise (sf_, blob_);
            }

            template<>
            [[maybe_unused]]
            void _memberSerialiser (
                const std::string & m,
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "Serializable" << std::endl);
                sf_.writeStringSingle (m, *this, blob_);
            }

            void _serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "::" << name() << std::endl); // NOLINT

                sf_.startRestricted (*this, blob_);
                serialiseImpl (sf_, blob_);

                for (const auto & i: *this) {
                    _memberSerialiser (i, sf_, blob_);
                }
            }

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

template<typename T, typename A>
struct is_std_vector<amqp::serializable::SerializableVector<T, A>> : std::true_type {
    static std::string fun () {
        return "java.util.List<" + javaTypeName<T> () + ">";
    }
};

/******************************************************************************/
