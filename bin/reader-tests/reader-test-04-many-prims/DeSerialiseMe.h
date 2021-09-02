#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner : public amqp::serializable::Serializable {
    private :
        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        int m_val1;
        int m_val2;
        int m_val3;
        int m_val4;
        int m_val5;
        int m_val6;

        explicit Inner (int a, int b, int c, int d, int e, int f)
            : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
            , m_val1 (a)
            , m_val2 (b)
            , m_val3 (c)
            , m_val4 (d)
            , m_val5 (e)
            , m_val6 (f)
        { }

        virtual ~Inner() = default;

        [[nodiscard]]
        static std::list<std::any>
        deserialiseImpl (
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        explicit Inner (const std::list<std::any> &);
};

/******************************************************************************/

class Outer : public amqp::serializable::Serializable {
    private :
        Inner   m_a;

        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Outer (int a, int b, int c, int d, int e, int f)
            : Serializable (javaTypeName<decltype(this)>(), "fingerprint456")
            , m_a (Inner (a, b, c, d, e, f))
        { }

        explicit Outer (const std::list<std::any> &);

        virtual ~Outer() = default;

        static std::list<std::any> deserialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[nodiscard]]
        const decltype (m_a) & a() const {
            return m_a;
        }
};

/******************************************************************************/
