#include "SerialiserFactoryInternal.h"

#include "amqp/include/ModifiableAMQPBlob.h"
#include "amqp/src/ModifiableAMQPBlobImpl.h"

/******************************************************************************/

uPtr<amqp::ModifiableAMQPBlob>
amqp::internal::assembler::
SerialiserFactoryInternal::blob() const  {
    return std::make_unique<amqp::internal::ModifiableAMQPBlobImpl>();
}

/******************************************************************************/

