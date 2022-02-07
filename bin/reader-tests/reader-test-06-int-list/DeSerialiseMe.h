#pragma once

#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/serializable/SerializableVector.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class DeSerialiseMe : public amqp::serializable::Serializable<DeSerialiseMe> {
    private :
        amqp::serializable::SerializableVector<int> m_val;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        DeSerialiseMe (std::initializer_list<int> list_)
            : Serializable (javaTypeName<decltype(this)>())
            , m_val (list_)
        { }

        explicit DeSerialiseMe (const std::vector<std::any> &);

        [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[maybe_unused]] [[nodiscard]] const std::vector<int> & val() const {
            return m_val;
        }
};

/******************************************************************************/
