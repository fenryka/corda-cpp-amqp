#include "SerialiseMe.h"

/******************************************************************************
 *
 * Fingerprints for our types
 *
 ******************************************************************************/

template<>
const std::string amqp::serializable::Fingerprint<MapIntInt>::val = "MapIntInt"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<amqp::serializable::SerializableMap<int, int>>::val = "MAP"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::map<int, int>>::val = "MAP2-int-int"; // NOLINT

/******************************************************************************
 *
 * MapIntInt impl
 *
 ******************************************************************************/

void
MapIntInt::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_map, "m_map", *this, blob_);
}

/******************************************************************************/
