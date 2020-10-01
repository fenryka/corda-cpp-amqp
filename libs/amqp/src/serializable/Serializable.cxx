#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/assembler/SerialiserFactory.h"

uPtr<amqp::AMQPBlob>
amqp::serializable::
Serializable::serialize(const amqp::assembler::SerialiserFactory & sf_) const {
    return sf_.serialize (*this);
}


