#include "SerialiseMe.h"

#include "corda-utils/include/types.h"

/******************************************************************************/

void
ListOfLists::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.writeRestricted (m_list, "m_list", *this, blob_);
}

/******************************************************************************/

