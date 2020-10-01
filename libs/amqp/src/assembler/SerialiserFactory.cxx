#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::assembler::
SerialiserFactory::serialize (const amqp::serializable::Serializable &) const {
    return nullptr;
}

/******************************************************************************/

