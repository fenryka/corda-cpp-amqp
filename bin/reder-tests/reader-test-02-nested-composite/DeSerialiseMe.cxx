#include "DeSerialiseMe.h"

/******************************************************************************
 *
 * Inner
 *
 ******************************************************************************/

Inner::Inner (
    const std::list<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>(),
    "fingerprint123"
) {
    auto i = l_.begin();
    try {
        m_val = std::any_cast<int> (*i);
    } catch (std::bad_any_cast & e) {
        std::cerr << "ARSE" << std::endl;
    }
}

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write<int> (m_val, "m_val", *this, blob_);
}

/******************************************************************************/

[[maybe_unused]] // It's not, but compiler can't find it through the template invocation
std::list<std::any>
Inner::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::list<std::any> rtn;
    rtn.emplace_back (sf_.read<int> (blob_));

    std::cout << "Inner::deserialiseImple:" << rtn.size() << std::endl;
    return rtn;
}

/******************************************************************************
 *
 * Outer
 *
 ******************************************************************************/

Outer::Outer (const std::list<std::any> & l_) : Serializable (
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
std::list<std::any>
Outer::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::list<std::any> rtn;
    rtn.emplace_back (sf_.read<Inner> (blob_));
    return rtn;
}

/******************************************************************************/
