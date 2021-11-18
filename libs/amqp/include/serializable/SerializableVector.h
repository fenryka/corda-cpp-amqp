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
    class SerializableVector final
        : public std::vector<T, A>
        , public RestrictedSerializable<std::vector<T>>
    {
        private :
            friend class amqp::assembler::SerialiserFactory;

            static const std::string s_javaType;

            /**
             *
             */
            void _serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << "::" << this->name() << std::endl); // NOLINT

                amqp::internal::serializable::AutoRestrictedWrite ar (*this, blob_);

                for (const auto & i: *this) {
                    sf_.writeSingle<T> (i, *this, blob_);
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
            explicit SerializableVector()
                : std::vector<T>()
                , RestrictedSerializable<std::vector<T>> (javaTypeName<std::vector<T, A>>())
            { }

            SerializableVector(
                std::initializer_list<T> l_
            ) : std::vector<T>(l_)
              , RestrictedSerializable<std::vector<T>> (javaTypeName<std::vector<T, A>>())
            { }

            explicit SerializableVector(
                std::vector<T> && v_
            ) : std::vector<T>(v_)
              , RestrictedSerializable<std::vector<T>> (javaTypeName<std::vector<T, A>>())
            { }

            explicit SerializableVector(
                const std::vector<std::any> &
            ) : std::vector<T>()
                , RestrictedSerializable<std::vector<T>> (javaTypeName<std::vector<T, A>>())
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

            [[nodiscard]]
            const std::string & javaType() const override {
                return s_javaType;
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
            proton::attest_is_list(blob_.data(), __FILE__, __LINE__);
            DBG ("ARSE" << std::endl;)
            SerializableVector<T, A> v;
#if 0
            amqp::internal::serializable::AutoRestrictedRead ar (&v, blob_);

            while (true) {
                sf_.readSingle<T> (blob_);
            }
#endif

            /*
            std::vector<std::any> rtn;
            rtn.template emplace_back (v);
             */
        }
    };
}

/******************************************************************************/

template<typename T, typename A>
[[maybe_unused]]
const std::string
amqp::serializable::
SerializableVector<T, A>::s_javaType = "list"; // NOLINT

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
