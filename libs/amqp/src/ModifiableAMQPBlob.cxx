#include "ModifiableAMQPBlob.h"

#include <proton/codec.h>
#include "corda-utils/include/debug.h"

#include "amqp/include/serializable/Serializable.h"
#include "amqp/src/schema/descriptors/corda-descriptors/FieldDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/CompositeDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/SchemaDescriptor.h"
#include "amqp/src/schema/descriptors/corda-descriptors/EnvelopeDescriptor.h"
#include "amqp/src/serialiser/serialisers/property-serialisers/IntPropertySerialiserBase.h"

/******************************************************************************/

amqp::
ModifiableAMQPBlob::ModifiableAMQPBlob()
    : m_payload (pn_data (0)
) {

}

/******************************************************************************/

void
amqp::
ModifiableAMQPBlob::startComposite (
        const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__ << " - " << composite_.name() << " - " << composite_.fingerprint() << std::endl);

    auto key = std::make_pair (composite_.name(), composite_.fingerprint());

    DBG ("  key = [" << key.first << ", " << key.second << "]" << std::endl);

    auto it = m_schemas.find (key);

    DBG ("ARSE" << std::endl);

    if (it == m_schemas.end()) {
        DBG ("ARSE2" << std::endl);
        m_schemas[key] = {};
    }

    it = m_schemas.find (key);
    assert (it != m_schemas.end());

    pn_data_put_described (m_payload);

    DBG ("THINGS" << std::endl);

    pn_data_enter (m_payload);
    DBG ("THINGS2" << std::endl);
    pn_data_put_symbol (m_payload, pn_bytes ( composite_.fingerprint().size(), composite_.fingerprint().data()));
    DBG ("THINGS3" << std::endl);
    pn_data_put_list (m_payload);
    DBG ("THINGS4" << std::endl);
    pn_data_enter (m_payload);
    DBG ("THINGS5" << std::endl);
}

/******************************************************************************/

void
amqp::
ModifiableAMQPBlob::writeInt (
        int propertyValue_,
        const std::string & propertyName_,
        const amqp::serializable::Serializable & clazz_)
{
    DBG (__FUNCTION__ << "::" << propertyName_ << "::" << propertyValue_ << std::endl); // NOLINT

    auto key = std::make_pair (clazz_.name(), clazz_.fingerprint());

    assert (m_schemas.find (key) != m_schemas.end());

    DBG ("FOUND IT" << std::endl);

    m_schemas[key].emplace_back (
        internal::schema::descriptors::FieldDescriptor::makeProton(
            propertyName_,
            internal::serialiser::serialisers::IntPropertySerialiserBase::m_type,
            {}));

    pn_data_put_int (m_payload, propertyValue_);
}

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::
ModifiableAMQPBlob::toBlob() const {
    DBG (__FUNCTION__ << std::endl); // NOLINT

    std::vector<pn_data_t *> composites;
    for (const auto & schema : m_schemas) {
        composites.emplace_back (
            internal::schema::descriptors::CompositeDescriptor::makeProton (
                schema.first.first, {}, schema.first.second, schema.second));
    }


    auto schema = internal::schema::descriptors::SchemaDescriptor::makeProton(composites);
    auto envelope = internal::schema::descriptors::EnvelopeDescriptor::makeProton(
            m_payload, schema)




}

/******************************************************************************/
