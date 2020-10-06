#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class SerialiseMe : public amqp::serializable::Serializable {
    private :
        int m_a;
        int m_b;
        int m_c;

    /**
     * Overriding this lets us actually specify how to serialise
     * this class
     */
        [[nodiscard]] uPtr<amqp::AMQPBlob> serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            uPtr<amqp::ModifiableAMQPBlob>) const override;

    public :
        explicit SerialiseMe (int a_, int b_, int c_)
            : Serializable ("fingerprint123", "net.test")
            , m_a (a_)
            , m_b (b_)
            , m_c (c_)
        { }

        [[maybe_unused]] [[nodiscard]] int a() const {
            return m_a;
        }

        [[maybe_unused]] [[nodiscard]] int b() const {
            return m_b;
        }

        [[maybe_unused]] [[nodiscard]] int c() const {
            return m_c;
        }
};

/******************************************************************************/
