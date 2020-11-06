#pragma once

/******************************************************************************/

#include <map>

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

    template <typename K, typename V, typename C = std::less<K>, typename A = std::allocator<std::pair<const K, V>>>
    class SerializableMap final : public std::map<K, V, C, A>, public Serializable {
        protected :
            void serialiseImpl (
                const amqp::assembler::SerialiserFactory &,
                ModifiableAMQPBlob &
            ) const override {
                DBG (__FUNCTION__ << std::endl);
            }

        public :
            SerializableMap() = delete;

            explicit SerializableMap(
                const std::string & fingerprint_
            ) : std::map<K,V,C, A>()
              , Serializable (javaTypeName<std::map<K,V,C,A>>(), fingerprint_)
            { }

            SerializableMap(
                const std::string & fingerprint_,
                std::initializer_list<std::pair<const K, V>> l_
            ) : std::map<K,V,C,A>(l_)
              , Serializable (javaTypeName<std::map<K, V, C, A>>(), fingerprint_)
            { }

            [[maybe_unused]] SerializableMap(
                const std::string & fingerprint_,
                std::map<K, V, C, A> && v_
            ) : std::map<K, V, C, A>(v_)
              , Serializable (javaTypeName<std::map<K, V, C, A>>(), fingerprint_)
            { }

            void serialise (
                const amqp::assembler::SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
//                return _serialise (sf_, blob_);
            }

            [[nodiscard]]
            uPtr<AMQPBlob> serialise (
                const amqp::assembler::SerialiserFactory & sf_
            ) const override {
                auto blob = sf_.blob();
//                _serialise (sf_, *blob);
                return blob->toBlob();
            }

    };

}

/******************************************************************************/
