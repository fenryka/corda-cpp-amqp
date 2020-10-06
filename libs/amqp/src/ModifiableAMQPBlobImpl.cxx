#include "ModifiableAMQPBlobImpl.h"

#include <proton/codec.h>

#include "corda-utils/include/debug.h"

#include "amqp/include/serializable/Serializable.h"

#include "amqp/src/serialiser/serialisers/CompositeSerialiser.h"

#include "amqp/src/schema/descriptors/corda-descriptors/CompositeDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/SchemaDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/EnvelopeDescriptor.h"

/******************************************************************************/

amqp::internal::
ModifiableAMQPBlobImpl::ModifiableAMQPBlobImpl()
    : m_payload (pn_data (0)
) {

}

/******************************************************************************/

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

    auto key = std::make_pair (composite_.name(), composite_.fingerprint());

    DBG ("    key = ["
        << key.first
        << ", "
        << key.second
        << "]"
        << std::endl); // NOLINT

    auto it = m_schemas.find (key);

    if (it == m_schemas.end()) {
        m_schemas[key] = {};
    }

    it = m_schemas.find (key);
    assert (it != m_schemas.end());

    pn_data_put_described (m_payload);

    pn_data_enter (m_payload);
    pn_data_put_symbol (m_payload, pn_bytes ( composite_.fingerprint().size(), composite_.fingerprint().data()));
    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::writeComposite (
    const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__ << "::" << composite_.name() << std::endl);

    auto key = std::make_pair (composite_.name(), composite_.fingerprint());

    assert (m_schemas.find (key) != m_schemas.end());

    DBG ("FOUND IT" << std::endl); // NOLINT

    m_schemas[key].emplace_back (
        internal::schema::descriptors::FieldDescriptor::makeProton(
            composite_.name(),
            composite_.fingerprint(),
            {}));
}

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::internal::
ModifiableAMQPBlobImpl::toBlob() const {
    DBG (__FUNCTION__ << ":: m_schemas.size() = " << m_schemas.size() << std::endl); // NOLINT

    std::vector<pn_data_t *> composites;
    for (const auto & schema : m_schemas) {
        composites.emplace_back (
            schema::descriptors::CompositeDescriptor::makeProton (
                schema.first.first, {}, schema.first.second, schema.second));
    }

    auto schema = schema::descriptors::SchemaDescriptor::makeProton (composites);
    auto envelope = schema::descriptors::EnvelopeDescriptor::makeProton (
            m_payload, schema);

    return std::make_unique<amqp::AMQPBlob>(envelope);
}

/******************************************************************************/
