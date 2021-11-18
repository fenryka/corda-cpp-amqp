#include "DeSerialiseMe.h"

/******************************************************************************
 *
 *  Fingerprints for our types
 *
 ******************************************************************************/

template<> const std::string amqp::serializable::Fingerprint<Inner>::val = "Inner123";
template<> const std::string amqp::serializable::Fingerprint<Outer>::val = "Outer123";

/******************************************************************************
 *
 * Inner
 *
 ******************************************************************************/

Inner::Inner (
    const std::vector<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>()
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
std::vector<std::any>
Inner::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<int> (blob_));

    std::cout << "Inner::deserialiseImple:" << rtn.size() << std::endl;
    return rtn;
}

/******************************************************************************
 *
 * Outer
 *
 ******************************************************************************/

Outer::Outer (const std::vector<std::any> & l_) : Serializable (
    javaTypeName<decltype(this)>()),
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
