#include "DeSerialiseMe.h"
#include "amqp/include/serializable/SerializableVector.h"

/******************************************************************************/

template<> const std::string amqp::serializable::Fingerprint<DeSerialiseMe>::val = "DSMe-123"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<std::vector<int>>::val = "IntVector"; // NOLINT

/******************************************************************************/

void
DeSerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_val, "m_val", *this, blob_);
}

/******************************************************************************/

DeSerialiseMe::DeSerialiseMe (
    const std::vector<std::any> & l_
) : Serializable (javaTypeName<decltype(this)>())
  , m_val { }
{
    /*
    auto i = l_.begin();
    m_val = std::any_cast<int> (*i++);
    m_val2 = std::any_cast<int *> (*i);

    DBG ("m_val = " << m_val << std::endl); // NOLINT
    DBG ("m_val2 = " << *m_val2 << std::endl); // NOLINT
     */
}

/******************************************************************************/

[[maybe_unused]] // It's not, but compiler can't find it through the template invocation
std::vector<std::any>
DeSerialiseMe::deserialiseImpl(
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_)
{
    DBG (__FUNCTION__ << std::endl);
    std::vector<std::any> rtn;

    rtn.emplace_back (sf_.read<amqp::serializable::SerializableVector<int>> (blob_));

    return rtn;
}

/******************************************************************************/
