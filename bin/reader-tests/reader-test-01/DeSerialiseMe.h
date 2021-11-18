#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class DeSerialiseMe : public amqp::serializable::Serializable<DeSerialiseMe> {
    private :
        int   m_val;
        int * m_val2;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit DeSerialiseMe (int val_)
            : Serializable (javaTypeName<decltype(this)>())
            , m_val (val_)
            , m_val2 { new int (val_) }
        { }

        explicit DeSerialiseMe (const std::vector<std::any> &);

        [[maybe_unused]]
        static std::vector<std::any> deserialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            const amqp::AMQPBlob &);

        [[maybe_unused]] [[nodiscard]] int val() const {
            return m_val;
        }

        [[maybe_unused]] [[nodiscard]] int val2() const {
            return *m_val2;
        }
};

/******************************************************************************/
