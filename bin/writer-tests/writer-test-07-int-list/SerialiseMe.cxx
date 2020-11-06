#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

/******************************************************************************/

void
ContainsList::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    sf_.write (m_list, "m_list", *this, blob_);
}

/******************************************************************************/

