#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class SerialiseMe : public amqp::serializable::Serializable {
    private :
        int m_val;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        [[nodiscard]] uPtr<amqp::AMQPBlob> serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            uPtr<amqp::ModifiableAMQPBlob>) const override;

    public :
        explicit SerialiseMe (int val_)
            : Serializable ("fingerprint123", "net.test")
            , m_val (val_)
        { }

        [[maybe_unused]] [[nodiscard]] int val() const {
            return m_val;
        }
};

/******************************************************************************/
