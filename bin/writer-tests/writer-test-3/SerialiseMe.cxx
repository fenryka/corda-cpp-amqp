#include "SerialiseMe.h"

/******************************************************************************/

void
SerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.writeStringPair (m_a, "m_a", *this, blob_);
    sf_.writeStringPair  (m_b, "m_b", *this, blob_);
}

/******************************************************************************/
