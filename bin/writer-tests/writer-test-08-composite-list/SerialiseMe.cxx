#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

/******************************************************************************/

void
Composite::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
    sf_.write (m_b, "m_b", *this, blob_);
}

void
CompositeList::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    sf_.writeRestricted (m_list, "m_list", *this, blob_);
}

/******************************************************************************/

