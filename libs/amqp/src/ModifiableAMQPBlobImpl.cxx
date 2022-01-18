#include "ModifiableAMQPBlobImpl.h"

#include <proton/codec.h>
#include "amqp/include/serializable/RestrictedSerializable.h"

#include "corda-utils/include/debug.h"

#include "amqp/include/serializable/Serializable.h"

#include "amqp/src/schema/descriptors/corda-descriptors/SchemaDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/EnvelopeDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/CompositeDescriptor.h"

/******************************************************************************/

amqp::internal::
ModifiableAMQPBlobImpl::ModifiableAMQPBlobImpl()
    : m_payload (pn_data (0))
{

}

/******************************************************************************/

inline
std::pair<std::string, std::string>
amqp::internal::
ModifiableAMQPBlobImpl::key (const amqp::serializable::SerializableBase & s_) {
    return std::make_pair (s_.name(), s_.fingerprint());
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::startSerializable (
    const amqp::serializable::SerializableBase & s_
) {
    DBG ("  startSerializable: " << s_.fingerprint() << std::endl);
    pn_data_put_described (m_payload);
    pn_data_enter (m_payload);
    pn_data_put_symbol (
        m_payload,
        pn_bytes (
            s_.fingerprint().size(),
            s_.fingerprint().data()));
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
    const amqp::serializable::SerializableBase & composite_
) {
    DBG (__FUNCTION__
        << " - "
        << composite_.name()
        << " - "
        << composite_.fingerprint()
        << std::endl); // NOLINT

    auto id = key (composite_);
    if (m_schemas.find (id) == m_schemas.end()) {
        m_schemas[id] = std::make_unique<CompositeBlob>();
    }

    startSerializable (composite_);

    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::startRestricted (
    const amqp::serializable::SerializableBase & restricted_
) {
    DBG (__FUNCTION__
             << " - "
             << restricted_.name()
             << " - "
             << restricted_.fingerprint()
             << std::endl); // NOLINT

    auto id = key (restricted_);
    if (m_schemas.find (id) == m_schemas.end()) {
        m_schemas[id] = std::make_unique<ListBlob>(restricted_.javaType());
    }

    startSerializable (restricted_);

    if (restricted_.javaType() == "map") {
        pn_data_put_map (m_payload);
    } else if (restricted_.javaType() == "list") {
        pn_data_put_list (m_payload);
    } else {
        std::stringstream ss;
        ss << "Unknown restricted type. " << __FILE__ << "::" << __LINE__;
        throw std::runtime_error (ss.str());
    }
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::endComposite (
    const amqp::serializable::SerializableBase & composite_
) {
    DBG ("endComposite - " << composite_.name() << std::endl);
    pn_data_exit (m_payload);
    pn_data_exit (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeNull (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::SerializableBase & parent_
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
ModifiableAMQPBlobImpl::endRestricted (
    const amqp::serializable::SerializableBase & restricted_
) {
    DBG ("endRestricted - " << restricted_.name() << std::endl);
    pn_data_exit (m_payload);
    pn_data_exit (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeComposite (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::SerializableBase & composite_
) {
    DBG (__FUNCTION__
        << "::" << composite_.name() << std::endl); // NOLINT

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
ModifiableAMQPBlobImpl::writeRestricted (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::SerializableBase & restricted_
) {
    DBG (__FUNCTION__ << "::" << restricted_.name() << std::endl); // NOLINT

    auto id = key (restricted_);

    assert (m_schemas.find (id) != m_schemas.end());

    auto & blob = dynamic_cast<CompositeBlob &>(*m_schemas[id]);

    if (blob.m_schemas.find (propertyName_) == blob.end()) {
        blob.m_schemas[propertyName_] =
            schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                "*",
                { propertyType_ }
            );
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

    /*
     *
     */
    std::vector<pn_data_t *> schemas;
    for (const auto & schema : m_schemas) {
        DBG ("    * "
            << schema.first.first
            << ": "
            << schema.second->size()
            << std::endl); // NOLINT

        schemas.emplace_back (
            schema.second->make (schema.first.first, schema.first.second));
    }

    auto schema = schema::descriptors::SchemaDescriptor::makeProton (
        schemas);

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
