#include "SerialiseMe.h"

/******************************************************************************/

uPtr<amqp::AMQPBlob>
SerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    uPtr<amqp::ModifiableAMQPBlob> blob_
) const {
    sf_.writeComposite (*this, *blob_);
    sf_.writeInt (m_val, "m_val", *this, *blob_);

    return blob_->toBlob();
}

/******************************************************************************/
