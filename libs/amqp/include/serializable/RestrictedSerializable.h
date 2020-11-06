#pragma once

/******************************************************************************/

#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

namespace amqp::internal::serializable {

    struct AutoRestricted {
        const amqp::serializable::Serializable & m_s;
        amqp::ModifiableAMQPBlob & m_b;

        AutoRestricted (decltype(m_s) s_, decltype(m_b) b_) : m_s (s_), m_b (b_) {
            amqp::assembler::SerialiserFactory::startRestricted (m_s, m_b);
        }

        ~AutoRestricted() {
            amqp::assembler::SerialiserFactory::endRestricted (m_s, m_b);
        }
    };

};

/******************************************************************************/
