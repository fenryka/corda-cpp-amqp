#pragma once

#include <utility>

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Composite : public amqp::serializable::Serializable<Composite> {
    private:
        std::string m_a;
        double m_b;

        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        Composite (std::string  a_, double b_)
            : Serializable<Composite> (javaTypeName<decltype(this)>())
            , m_a (std::move(a_))
            , m_b (b_)
        {
        }

        virtual ~Composite() = default;
};

/******************************************************************************/

class CompositeList : public amqp::serializable::Serializable<CompositeList> {
    private :
        amqp::serializable::SerializableVector<Composite> m_list;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit CompositeList (std::vector<Composite> list_)
            : Serializable<CompositeList> (javaTypeName<decltype(this)>())
            , m_list (std::move (list_))
        {
        }

        virtual ~CompositeList() = default;
};

/******************************************************************************/

