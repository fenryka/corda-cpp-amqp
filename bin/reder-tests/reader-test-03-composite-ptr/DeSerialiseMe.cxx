#include "DeSerialiseMe.h"

/******************************************************************************/

Inner::Inner (
    const std::vector<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>(),
    "fingerprint123")
{

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
 *
 *
 ******************************************************************************/

Outer::Outer (
    const std::vector<std::any> & l_
) : Serializable (
    javaTypeName<decltype(this)>(),
    "fingerprint456")
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

