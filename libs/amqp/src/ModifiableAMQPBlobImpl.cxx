#include "ModifiableAMQPBlobImpl.h"

#include <proton/codec.h>

#include "corda-utils/include/debug.h"

#include "amqp/include/serializable/Serializable.h"

#include "amqp/src/schema/descriptors/corda-descriptors/SchemaDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/EnvelopeDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/CompositeDescriptor.h"

/******************************************************************************/

amqp::internal::
ModifiableAMQPBlobImpl::ModifiableAMQPBlobImpl()
    : m_payload (pn_data (0)
) {

}

/******************************************************************************/

inline
std::pair<std::string, std::string>
amqp::internal::
ModifiableAMQPBlobImpl::key (const amqp::serializable::Serializable & s_) {
    return std::make_pair (s_.name(), s_.fingerprint());
}

/******************************************************************************/

/*
 *
 * For now we're just going to accept that in recursive class definitions
 * we're going to do some unneeded lifting in terms of looking
 * in the map
 *
 */
void
amqp::internal::
ModifiableAMQPBlobImpl::startComposite (
    const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__
        << " - "
        << composite_.name()
        << " - "
        << composite_.fingerprint()
        << std::endl); // NOLINT

    auto id = key (composite_);

    DBG ("    key = ["
        << id.first
        << ", "
        << id.second
        << "]"
        << std::endl); // NOLINT

    auto it = m_schemas.find (id);

    if (it == m_schemas.end()) {
        m_schemas[id] = std::make_unique<CompositeBlob>();
    }

    pn_data_put_described (m_payload);

    pn_data_enter (m_payload);
    pn_data_put_symbol (
        m_payload,
        pn_bytes (
            composite_.fingerprint().size(),
            composite_.fingerprint().data()));

    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeNull (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & parent_
) {
    DBG (__FUNCTION__
             << "::" << propertyName_
             << "::" << NULL << " "
             << "PARENT: " << parent_.name() << std::endl); // NOLINT

    auto id = key (parent_);

    assert (m_schemas.find (id) != m_schemas.end());

    auto & blob = dynamic_cast<CompositeBlob &>(*m_schemas[id]);

    if (blob.m_schemas.find (propertyName_) == blob.end()) {
        std::cout << propertyName_ << " missing :(" << std::endl;
        blob.m_schemas[propertyName_] =
            internal::schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                propertyType_,
                {},
                "", "",
                true,
                false);
    }

    DBG ("WRITE IT" << std::endl); // NOLINT

    pn_data_put_null (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::startRestricted (
    const amqp::serializable::Serializable & restricted_
) {
    DBG (__FUNCTION__
             << " - "
             << restricted_.name()
             << " - "
             << restricted_.fingerprint()
             << std::endl); // NOLINT

    auto id = key (restricted_);

    DBG ("    key = ["
             << id.first
             << ", "
             << id.second
             << "]"
             << std::endl); // NOLINT

    auto it = m_schemas.find (id);

    if (it == m_schemas.end()) {
        m_schemas[id] = std::make_unique<ListBlob>(restricted_.name());
    }

    pn_data_put_described (m_payload);

    pn_data_enter (m_payload);
    pn_data_put_symbol (
        m_payload,
        pn_bytes (
            restricted_.fingerprint().size(),
            restricted_.fingerprint().data()));

    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::startList (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & parent_
) {
    DBG (__FUNCTION__
             << " - "
             << propertyName_
             << " - "
             << propertyType_
             << std::endl); // NOLINT

    auto id = key (parent_);

    auto it = m_schemas.find (id);

    if (it == m_schemas.end()) {
        m_schemas[id] = {};
    }

    pn_data_put_described (m_payload);

    pn_data_enter (m_payload);
    pn_data_put_symbol (
        m_payload,
        pn_bytes (
            4,
            "list"));

    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeComposite_ (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__
        << "::"
        << composite_.name()
        << std::endl); // NOLINT

    auto id = key (composite_);

    assert (m_schemas.find (id) != m_schemas.end());

    auto & blob = dynamic_cast<CompositeBlob &>(*m_schemas[id]);

    if (blob.m_schemas.find (propertyName_) == blob.end()) {
        blob.m_schemas[propertyName_] =
            schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                propertyType_,
                {});
    }
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeRestricted_ (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & restricted_
) {
    DBG (__FUNCTION__
             << "::"
             << restricted_.name()
             << std::endl); // NOLINT

    auto id = key (restricted_);

    assert (m_schemas.find (id) != m_schemas.end());

    auto & blob = dynamic_cast<CompositeBlob &>(*m_schemas[id]);

    if (blob.m_schemas.find (propertyName_) == blob.end()) {
        blob.m_schemas[propertyName_] =
            schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                propertyType_,
                {});
    }
}

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::internal::
ModifiableAMQPBlobImpl::toBlob() const {
    DBG (__FUNCTION__
        << ":: m_schemas.size() = "
        << m_schemas.size()
        << std::endl); // NOLINT

    std::vector<pn_data_t *> composites;
    for (const auto & schema : m_schemas) {
        DBG ("    * "
            << schema.first.first
            << ": "
            << schema.second->size()
            << std::endl); // NOLINT

        composites.emplace_back (
            schema.second->make (schema.first.first, schema.first.second));
    }

    auto schema = schema::descriptors::SchemaDescriptor::makeProton (
        composites);

    auto envelope = schema::descriptors::EnvelopeDescriptor::makeProton (
        m_payload, schema);

    return std::make_unique<amqp::AMQPBlob>(envelope);
}

/******************************************************************************/

#if defined AMQP_DEBUG && AMQP_DEBUG >= 1

void
amqp::internal::
ModifiableAMQPBlobImpl::dump() const {
    for (const auto &i: m_schemas) {
        std::cout << "  *    [ "
                  << i.first.first
                  << ", "
                  << i.first.second
                  << "] : " << i.second->size() << std::endl;
    }
}

#else

void
amqp::internal::
ModifiableAMQPBlobImpl::dump() const {}

#endif

/******************************************************************************/
