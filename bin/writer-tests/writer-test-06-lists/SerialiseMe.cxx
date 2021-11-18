#include "SerialiseMe.h"

#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

/******************************************************************************/

template<>
const std::string amqp::serializable::Fingerprint<ContainsList>::val = "Contains-List-123"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<std::string>>::val = "vector-of-string"; // NOLINT

/******************************************************************************/

void
ContainsList::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    sf_.write (m_list, "m_list", *this, blob_);
}

/******************************************************************************/

