#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class SerialiseMe : public amqp::serializable::Serializable {
    private :
        int         m_val;
        std::string m_val2;


        [[nodiscard]] uPtr<amqp::serialiser::ISerialiser> build (
            amqp::assembler::SerialiserFactory &
        ) const override;

        [[nodiscard]] uPtr<amqp::AMQPBlob> serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            uPtr<amqp::ModifiableAMQPBlob>) const override;

    public :
        explicit SerialiseMe (int val_, std::string val2_)
            : Serializable ("fingerprint123", "net.test")
            , m_val (val_)
            , m_val2 (std::move (val2_))
        { }

        [[maybe_unused]] [[nodiscard]] int val() const {
            return m_val;
        }

        [[maybe_unused]] [[nodiscard]] const std::string & val2() const {
            return m_val2;
        }
};

/******************************************************************************/
