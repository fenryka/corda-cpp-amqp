#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

void
Recursive::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    sf_.writeInt (m_a, "m_a", *this, blob_);
    sf_.writeString (m_b, "m_b", *this, blob_);
    writeCompositeM (sf_, m_c, *this, blob_);
}

/******************************************************************************/

