#include "SerialiseMe.h"

/******************************************************************************/

uPtr<amqp::AMQPBlob>
SerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    uPtr<amqp::ModifiableAMQPBlob> blob_
) const {
    sf_.writeComposite (*this, *blob_);
    sf_.writeInt (m_a, "m_a", *this, *blob_);
    sf_.writeInt (m_b, "m_b", *this, *blob_);
    sf_.writeInt (m_c, "m_c", *this, *blob_);

    return blob_->toBlob();
}

/******************************************************************************/
