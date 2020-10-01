#pragma once

#include "include/serializable/Serializable.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class SerialiseMe : public amqp::serializable::Serializable {
    private :
        int m_val;

        [[nodiscard]] uPtr<amqp::serialiser::ISerialiser> build() const override;


    public :
        explicit SerialiseMe (int val_)
            : Serializable ("123")
            , m_val (val_)
        { }

        [[nodiscard]] int val() const {
            return m_val;
        }
};

/******************************************************************************/
