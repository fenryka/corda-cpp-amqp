#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/include/serializable/RestrictedSerializable.h"

/******************************************************************************/

amqp::internal::serializable::
AutoRestrictedWrite::AutoRestrictedWrite(
    decltype(m_s) s_, decltype(m_b) b_
) : m_s (s_), m_b (b_) {
    amqp::assembler::SerialiserFactory::startRestricted (m_s, m_b);
}

/******************************************************************************/

amqp::internal::serializable::
AutoRestrictedWrite::~AutoRestrictedWrite() {
    amqp::assembler::SerialiserFactory::endRestricted (m_s, m_b);
}

/******************************************************************************
 *
 *
 ******************************************************************************/

amqp::internal::serializable::
AutoRestrictedRead::AutoRestrictedRead (
    decltype (m_s) s_, decltype (m_b) b_
) : m_s (s_)
  , m_b (b_)
{ }

/******************************************************************************/

