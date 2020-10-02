#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory {
        public :
            void writeComposite ();
            virtual void writeInt(int, const std::string &, ModifiableAMQPBlob &) const = 0;
    };

}
/******************************************************************************/
