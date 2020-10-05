#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

amqp::serializable::
Serializable::Serializable (
    std::string fingerprint_,
    std::string namespace_
) : m_name (typeid(this).name())
  , m_fingerprint (std::move (fingerprint_))
  , m_namespace (std::move (namespace_)
) {

}

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::serializable::
Serializable::serialise (
        const amqp::assembler::SerialiserFactory & sf_
) const {
    return serialiseImpl (sf_, std::make_unique<amqp::ModifiableAMQPBlob>());
}

/******************************************************************************/

const std::string &
amqp::serializable::
Serializable::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::serializable::
Serializable::fingerprint() const {
    return m_fingerprint;
}

/******************************************************************************/

const std::string &
amqp::serializable::
Serializable::javaNamespace() const {
    return m_namespace;
}

/******************************************************************************/
