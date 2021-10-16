#include "DeSerialiseMe.h"

/******************************************************************************/

void
DeSerialiseMe::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write<int> (m_val, "m_val", *this, blob_);
    sf_.write<int *> (m_val2, "m_val2", *this, blob_);
}

/******************************************************************************/

DeSerialiseMe::DeSerialiseMe (
    const std::vector<std::any> & l_
) : Serializable (javaTypeName<decltype(this)>(), "fingerprint123") {
    auto i = l_.begin();
    m_val = std::any_cast<int> (*i++);
    m_val2 = std::any_cast<int *> (*i);

    DBG ("m_val = " << m_val << std::endl);
    DBG ("m_val2 = " << *m_val2 << std::endl);
}

/******************************************************************************/

[[maybe_unused]] // It's not, but compiler can't find it through the template invocation
std::vector<std::any>
DeSerialiseMe::deserialiseImpl(
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_)
{
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int *> (blob_));

    return rtn;
}

/******************************************************************************/
