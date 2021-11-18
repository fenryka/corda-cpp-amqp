#pragma once

#include "amqp/include/serializable/Serializable.h"

/******************************************************************************/

namespace amqp::internal::serializable {

    struct AutoRestrictedWrite {
        const amqp::serializable::SerializableBase & m_s;
        amqp::ModifiableAMQPBlob & m_b;

        AutoRestrictedWrite (decltype(m_s), decltype(m_b) b_);
        ~AutoRestrictedWrite();
    };

    struct [[maybe_unused]] AutoRestrictedRead {
        const amqp::serializable::SerializableBase & m_s;
        amqp::AMQPBlob & m_b;

        [[maybe_unused]] AutoRestrictedRead (decltype(m_s), decltype(m_b) b_);
        ~AutoRestrictedRead() = default;
    };

}

/******************************************************************************/

namespace amqp::serializable {

    template<typename FINGERPRINT>
    class RestrictedSerializable : public SerializableBase, private Fingerprint<FINGERPRINT> {
        public :
            explicit RestrictedSerializable (
                std::string name_
            ) : SerializableBase (std::move (name_))
            { }

            [[nodiscard]] const std::string & fingerprint() const override {
                return this->_fingerprint();
            }
    };

}

/******************************************************************************/
