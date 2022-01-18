#pragma once

/******************************************************************************/

#include <utility>

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableMap.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class Inner : public amqp::serializable::Serializable<Inner> {
    private :
        std::string m_a;

    public :
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

        explicit Inner (std::string a_)
            : Serializable<Inner> (javaTypeName<decltype(this)>())
            , m_a (std::move(a_))
        { }

        virtual ~Inner() = default;
};

/******************************************************************************/

class DeSerialiseMe : public amqp::serializable::Serializable<DeSerialiseMe> {
    private :
        amqp::serializable::SerializableMap<int, Inner> m_map;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit DeSerialiseMe ()
            : Serializable<DeSerialiseMe> (javaTypeName<decltype(this)>())
        {
            m_map.emplace (1, Inner ("one"));
            m_map.emplace(2, Inner ("two"));
            m_map.emplace(4, Inner ("four"));
            m_map.emplace(8, Inner ("eight"));
            m_map.emplace(16, Inner ("sixteen"));
            m_map.emplace(32, Inner ("thirty two"));
        }

    virtual ~DeSerialiseMe() = default;
};

/******************************************************************************/

