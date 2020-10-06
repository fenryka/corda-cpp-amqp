#include "SerialiseMe.h"

/******************************************************************************/

uPtr<amqp::AMQPBlob>
SerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    uPtr<amqp::ModifiableAMQPBlob> blob_
) const {
    sf_.writeComposite (*this, *blob_);
    sf_.writeString (m_a, "m_a", *this, *blob_);
    sf_.writeString (m_b, "m_b", *this, *blob_);

    return blob_->toBlob();
}

/******************************************************************************/
