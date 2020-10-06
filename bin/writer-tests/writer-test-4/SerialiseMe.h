#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner : public amqp::serializable::Serializable {
    private :
        int m_a;
        std::string m_b;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Inner (int a_, std::string b_)
            : Serializable ("Inner", "fingerprint123", "net.test")
            , m_a (a_)
            , m_b (std::move (b_))
        { }
};

/******************************************************************************/

class Outer : public amqp::serializable::Serializable {
    private :
        Inner m_a;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Outer (Inner & a_)
            : Serializable ("Outer", "fingerprintABC", "net.test")
            , m_a (std::move (a_))
        { }
};

/******************************************************************************/
