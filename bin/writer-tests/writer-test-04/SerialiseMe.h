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
        int m_a;
        std::string m_b;
        bool m_c;
        double m_d;
        float m_e;

    public :
        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

        explicit Inner (int a_, std::string b_, bool c_, double d_, float e_)
            : Serializable (javaTypeName<decltype(this)>())
            , m_a (a_)
            , m_b (std::move (b_))
            , m_c (c_)
            , m_d (d_)
            , m_e (e_)
        { }
};

/******************************************************************************/

class Outer : public amqp::serializable::Serializable<Outer> {
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
            : Serializable (javaTypeName<decltype(this)>())
            , m_a (std::move (a_))
        { }
};

/******************************************************************************/
