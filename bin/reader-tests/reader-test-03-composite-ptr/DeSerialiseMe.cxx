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
 * Inner impl
 *
 ******************************************************************************/

Inner::Inner (
    const std::vector<std::any> & l_
) : Serializable (javaTypeName<decltype(this)>())
  , m_val1 { std::any_cast<int>(l_[0])}
  , m_val2 { std::any_cast<int>(l_[1])}
{

}

/******************************************************************************/

void
Inner::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write<int> (m_val1, "m_val1", *this, blob_);
    sf_.write<int> (m_val2, "m_val2", *this, blob_);
}

/******************************************************************************/

std::vector<std::any>
Inner::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<int> (blob_));
    rtn.emplace_back (sf_.read<int> (blob_));

    std::cout << "Inner::deserialiseImpl:" << rtn.size() << std::endl;
    return rtn;
}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

Outer::Outer (
    const std::vector<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>())
  , m_a  { std::any_cast<Inner> (l_[0]) }
  , m_b { std::any_cast<Inner *> (l_[1]) }
{

}

/******************************************************************************/

void
Outer::serialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    amqp::ModifiableAMQPBlob & blob_
) const {
    sf_.write (m_a, "m_a", *this, blob_);
    sf_.write (m_b, "m_b", *this, blob_);
}

/******************************************************************************/

std::vector<std::any>
Outer::deserialiseImpl (
    const amqp::assembler::SerialiserFactory & sf_,
    const amqp::AMQPBlob & blob_
) {
    std::vector<std::any> rtn;
    rtn.emplace_back (sf_.read<Inner> (blob_));
    rtn.emplace_back (sf_.read<Inner *> (blob_));
    return rtn;
}

/******************************************************************************/

