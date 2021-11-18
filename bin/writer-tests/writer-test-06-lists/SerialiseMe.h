#pragma once

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class ContainsList;

/******************************************************************************/

class ContainsList : public amqp::serializable::Serializable<ContainsList> {
    private :
        amqp::serializable::SerializableVector<std::string> m_list;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit ContainsList (std::vector<std::string> list_)
            : Serializable (javaTypeName<decltype(this)>())
            , m_list (std::move (list_))
        {
        }
};

/******************************************************************************/

