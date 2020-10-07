#include "ModifiableAMQPBlobImpl.h"

#include <proton/codec.h>

#include "corda-utils/include/debug.h"

#include "amqp/include/serializable/Serializable.h"

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

        for (const auto &i : m_schemas) {
            DBG ("    * " << i.first.first << ": " << i.second.size() << std::endl);
        }
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
ModifiableAMQPBlobImpl::writeComposite (
    const std::string & propertyName_,
    const amqp::serializable::Serializable & parent_,
    const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__
        << "::"
        << parent_.name()
        << "::"
        << composite_.name()
        << std::endl); // NOLINT

    auto key = std::make_pair (parent_.name(), parent_.fingerprint());

    assert (m_schemas.find (key) != m_schemas.end());

    DBG ("FOUND IT ["
        << parent_.name()
        << ", "
        << parent_.fingerprint()
        << "] - m_schemas size - "
        << m_schemas[key].size()
        << std::endl); // NOLINT

    if (m_schemas[key].find(propertyName_) == m_schemas[key].end()) {
        m_schemas[key][propertyName_] =
            schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                composite_.name (),
                {});
    }

    DBG ("    schemas sz: "
        << m_schemas.size()
        << ", "
        << m_schemas[key].size()
        << std::endl); // NOLINT
}

/******************************************************************************/

uPtr<amqp::AMQPBlob>
amqp::internal::
ModifiableAMQPBlobImpl::toBlob() const {
    DBG (__FUNCTION__ << ":: m_schemas.size() = " << m_schemas.size() << std::endl); // NOLINT

    std::vector<pn_data_t *> composites;
    for (const auto & schema : m_schemas) {
        DBG ("    * " << schema.first.first << ": " << schema.second.size() << std::endl);

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

void
amqp::internal::
ModifiableAMQPBlobImpl::writeNull (
    const std::string &,
    const amqp::serializable::Serializable &
) {

}

/******************************************************************************/

void
amqp::internal::
ModifiableAMQPBlobImpl::dump() const {
    std::cout << "  * BLOB-DUMP" << std::endl;
    for (const auto &i: m_schemas) {
        std::cout << "  *    [ "
                  << i.first.first
                  << ", "
                  << i.first.second
                  << "] : " << i.second.size() << std::endl;
    }
}

/******************************************************************************/
