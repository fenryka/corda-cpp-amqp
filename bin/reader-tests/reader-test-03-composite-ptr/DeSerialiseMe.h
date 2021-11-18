#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner;
class Outer;

/******************************************************************************/

class Inner : public amqp::serializable::Serializable<Inner> {
    private :
        int m_val1;
        int m_val2;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Inner (int val1_, int val2_)
            : Serializable (javaTypeName<decltype(this)>())
            , m_val1 (val1_)
            , m_val2 (val2_)
        { }

        explicit Inner (const std::vector<std::any> &);

        virtual ~Inner() = default;

        [[nodiscard]]
        static std::vector<std::any>
        deserialiseImpl (
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[nodiscard]] int v1() const { return m_val1; }
        [[nodiscard]] int v2() const { return m_val2; }
};

/******************************************************************************/

class Outer : public amqp::serializable::Serializable<Outer> {
    private :
        Inner   m_a;
        Inner * m_b;

        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit Outer ()
            : Serializable (javaTypeName<decltype(this)>())
            , m_a (Inner (1, 2))
            , m_b (new Inner (3, 4))
        { }


        explicit Outer (const std::vector<std::any> &);

        virtual ~Outer() = default;

        [[nodiscard]]
        static std::vector<std::any>
        deserialiseImpl (
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[nodiscard]] const decltype(m_a) & a() const { return m_a; }
        [[nodiscard]] const decltype(m_b) & b() const { return m_b; }
};

/******************************************************************************/
