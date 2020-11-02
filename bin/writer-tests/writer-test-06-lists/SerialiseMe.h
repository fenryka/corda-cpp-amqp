#pragma once

#include "include/serializable/Serializable.h"
#include "include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class ContainsList : public amqp::serializable::Serializable {
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
            : Serializable (javaTypeName<decltype(this)>(),"fingerprint123")
            , m_list ("fingerprint456", std::move (list_))
        {
            std::cout << "m_list.name() = " << m_list.name() << std::endl;
        }
};

/******************************************************************************/

