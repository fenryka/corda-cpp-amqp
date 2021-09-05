#include "DeSerialiseMe.h"

/******************************************************************************
 *
 * Inner
 *
 ******************************************************************************/

Inner::Inner (
    const std::vector<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>(),
    "fingerprint123"
) {
    auto i = l_.begin();
    m_val1 = std::any_cast<int> (*i++);
    m_val2 = std::any_cast<int> (*i++);
    m_val3 = std::any_cast<int> (*i++);
    m_val4 = std::any_cast<int> (*i++);
    m_val5 = std::any_cast<int> (*i++);
    m_val6 = std::any_cast<int> (*i++);
}

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write<int> (m_val1, "m_val1", *this, blob_);
    sf_.write<int> (m_val2, "m_val2", *this, blob_);
    sf_.write<int> (m_val3, "m_val3", *this, blob_);
    sf_.write<int> (m_val4, "m_val4", *this, blob_);
    sf_.write<int> (m_val5, "m_val5", *this, blob_);
    sf_.write<int> (m_val6, "m_val6", *this, blob_);
}

/******************************************************************************/

[[maybe_unused]] // It's not, but compiler can't find it through the template invocation
std::vector<std::any>
Inner::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));

    std::cout << "Inner::deserialiseImpl:" << rtn.size() << std::endl;
    return rtn;
}

/******************************************************************************
 *
 * Outer
 *
 ******************************************************************************/

Outer::Outer (const std::vector<std::any> & l_) : Serializable (
    javaTypeName<decltype(this)>(),
    "fingerprint456"),
    m_a (std::any_cast<Inner>(l_.front()))
{
}

/******************************************************************************/

void
Outer::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
}

/******************************************************************************/

[[maybe_unused]] // It's not, but compiler can't find it through the template invocation
std::vector<std::any>
Outer::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<Inner> (blob_));
    return rtn;
}

/******************************************************************************/
