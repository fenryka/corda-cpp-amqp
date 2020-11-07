#pragma once

/******************************************************************************/

namespace amqp::serializable {
    class RestrictedSerializable;
}

/******************************************************************************/

namespace amqp::internal::serializable {

    struct AutoRestricted {
        const amqp::serializable::RestrictedSerializable & m_s;
        amqp::ModifiableAMQPBlob & m_b;

        AutoRestricted (decltype(m_s), decltype(m_b) b_);
        ~AutoRestricted();
    };

}

/******************************************************************************/

namespace amqp::serializable {

    class RestrictedSerializable : public Serializable {
        private :
            std::string m_javaType;

        public :
            RestrictedSerializable (
                std::string name_,
                std::string fingerprint_,
                std::string javaType_
            ) : Serializable (std::move (name_), std::move (fingerprint_))
                , m_javaType (std::move (javaType_))
            { }

            [[nodiscard]] const std::string & javaType() const {
                return m_javaType;
            }
    };

}

/******************************************************************************/
