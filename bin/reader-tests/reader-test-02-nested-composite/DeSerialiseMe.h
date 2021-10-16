#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner : public amqp::serializable::Serializable {
    private :
        int m_val;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Inner (int val_)
            : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
            , m_val (val_)
        { }

        virtual ~Inner() = default;

        [[nodiscard]]
        static std::vector<std::any>
        deserialiseImpl (
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        explicit Inner (const std::vector<std::any> &);

        [[nodiscard]]
        const decltype (m_val) & val() const {
            return m_val;
        }
};

/******************************************************************************/

class Outer : public amqp::serializable::Serializable {
    private :
        Inner   m_a;

        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Outer (int val_= 1)
            : Serializable (javaTypeName<decltype(this)>(), "fingerprint456")
            , m_a (Inner (val_))
        { }

        explicit Outer (const std::vector<std::any> &);

        virtual ~Outer() = default;

        static std::vector<std::any> deserialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[nodiscard]]
        const decltype (m_a) & a() const {
            return m_a;
        }
};

/******************************************************************************/
