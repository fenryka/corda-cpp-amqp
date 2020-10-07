#include "SerialiseMe.h"

/******************************************************************************/

void
SerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.writeInt (m_val, "m_val", *this, blob_);
}

/******************************************************************************/
