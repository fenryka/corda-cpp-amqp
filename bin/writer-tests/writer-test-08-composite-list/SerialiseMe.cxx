#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"

/******************************************************************************/

template<> const std::string amqp::serializable::Fingerprint<Composite>::val = "Composite123";
template<> const std::string amqp::serializable::Fingerprint<CompositeList>::val = "CopmositeList123";

/******************************************************************************/

void
Composite::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
    sf_.write (m_b, "m_b", *this, blob_);
}

/******************************************************************************/

void
CompositeList::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    sf_.write (m_list, "m_list", *this, blob_);
}

/******************************************************************************/

