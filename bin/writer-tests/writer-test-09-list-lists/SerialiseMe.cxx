#include "SerialiseMe.h"

#include "corda-utils/include/types.h"

/******************************************************************************/

template<>
const std::string amqp::serializable::Fingerprint<ListOfLists>::val = "LOL123"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<int>>::val = "intList"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<std::vector<int>>>::val = "ListIntList"; // NOLINT

/******************************************************************************/

void
ListOfLists::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_list, "m_list", *this, blob_);
}

/******************************************************************************/
