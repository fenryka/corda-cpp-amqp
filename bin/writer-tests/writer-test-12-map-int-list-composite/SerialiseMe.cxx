#include "SerialiseMe.h"

/******************************************************************************/

template<>
const std::string amqp::serializable::Fingerprint<Inner>::val = "FP-Inner"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<DeSerialiseMe>::val = "FP-DSM"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<int>>::val = "FP-IntVector"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<Inner>>::val = "FP-InnerVector"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::map<int, std::vector<Inner>>>::val = "FP-PANTS"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::map<int, amqp::serializable::SerializableVector<Inner>>>::val = "FP-PANTS"; // NOLINT

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
    sf_.write (m_b, "m_b", *this, blob_);
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

