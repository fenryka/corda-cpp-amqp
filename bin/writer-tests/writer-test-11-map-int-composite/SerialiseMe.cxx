#include "SerialiseMe.h"

/******************************************************************************/

template<>
const std::string amqp::serializable::Fingerprint<Inner>::val = "FP-Inner"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<DeSerialiseMe>::val = "FP-DSM"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::map<int, Inner>>::val = "FP-MapItoInner"; // NOLINT

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
}

/******************************************************************************/

void
DeSerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_map, "m_map", *this, blob_);
}

/******************************************************************************/

