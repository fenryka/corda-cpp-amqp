#pragma once

/******************************************************************************/

#include <utility>

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class ListOfLists : public amqp::serializable::Serializable {
    private :
        amqp::serializable::SerializableVector<
            amqp::serializable::SerializableVector<int> > m_list;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit ListOfLists (
            amqp::serializable::SerializableVector<amqp::serializable::SerializableVector<int>> list_
        ) : Serializable (javaTypeName<decltype(this)>(),"fingerprint123")
            , m_list (std::move (list_))
        {
        }

        virtual ~ListOfLists() = default;
};

/******************************************************************************/

