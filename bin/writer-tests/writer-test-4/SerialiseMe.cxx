#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl);

    sf_.writeInt (m_a, "m_a", *this, blob_);
    sf_.writeString (m_b, "m_b", *this, blob_);
}

/******************************************************************************/

void
Outer::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl);

    sf_.writeComposite (m_a, "m_a", *this, blob_);
}

/******************************************************************************/
