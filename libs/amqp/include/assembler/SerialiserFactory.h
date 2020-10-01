#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::assembler {

}

namespace amqp::assembler {

    class SerialiserFactory {
        public :
            [[nodiscard]] virtual uPtr<amqp::AMQPBlob> serialize (
                    const amqp::serializable::Serializable &) const = 0;

            virtual bool registerType (
                    const amqp::serializable::Serializable &) = 0;
    };

}
/******************************************************************************/
