#pragma once

/******************************************************************************/

#include <utility>

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableMap.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner : public amqp::serializable::Serializable {
    private :
        std::string m_a;
        amqp::serializable::SerializableVector<int> m_b;

    public :
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

        Inner (std::string a_, std::initializer_list<int> b_)
            : Serializable (javaTypeName<decltype(this)>(),"INNER")
            , m_a (std::move(a_))
            , m_b ("MAP-FP-1", b_)
        { }

        virtual ~Inner() = default;
};

/******************************************************************************/

class SerialiseMe : public amqp::serializable::Serializable {
    private :
        amqp::serializable::SerializableMap<int, amqp::serializable::SerializableVector<Inner>> m_map;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit SerialiseMe (
        ) : Serializable (javaTypeName<decltype(this)>(),"SERIALISE-ME-FP")
          , m_map ("MAP-FP-2")
        {
            Inner i1 = Inner ("a", {2, 3, 4});
            Inner i2 = Inner ("b", {5, 6, 7});
            Inner i3 = Inner ("c", {9, 10, 11});
            Inner i4 = Inner ("d", {12, 13, 14});

            amqp::serializable::SerializableVector<Inner> l1 ("LIST-FP", {i1, i2});
            amqp::serializable::SerializableVector<Inner> l2 ("LIST-FP", {i1, i2});

            m_map.emplace(1, l1);
            m_map.emplace(8, l2);

        }

    virtual ~SerialiseMe() = default;
};

/******************************************************************************/

