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
        m_schemas[id] = {};

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
ModifiableAMQPBlobImpl::writeNull (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & parent_
) {
    DBG (__FUNCTION__
             << "::"
             << propertyName_
             << "::"
             << NULL << " "
             << "PAREMT: " << parent_.name()
             << std::endl); // NOLINT

    auto id = key (parent_);

    assert (m_schemas.find (id) != m_schemas.end());

    if (m_schemas[id].find (propertyName_) == m_schemas[id].end()) {
        std::cout << propertyName_ << " missing :(" << std::endl;
        m_schemas[id][propertyName_] =
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
ModifiableAMQPBlobImpl::writeComposite (
    const std::string & propertyName_,
    const std::string & propertyType_,
    const amqp::serializable::Serializable & parent_,
    const amqp::serializable::Serializable & composite_
) {
    DBG (__FUNCTION__
        << "::"
        << parent_.name()
        << "::"
        << composite_.name()
        << std::endl); // NOLINT

    auto id = key (parent_);

    assert (m_schemas.find (id) != m_schemas.end());

    DBG ("FOUND IT ["
        << parent_.name()
        << ", "
        << parent_.fingerprint()
        << "] - m_schemas size - "
        << m_schemas[id].size()
        << std::endl); // NOLINT

    if (m_schemas[id].find (propertyName_) == m_schemas[id].end()) {
        m_schemas[id][propertyName_] =
            schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                propertyType_,
                {});
    }

    DBG ("    schemas sz: "
        << m_schemas.size()
        << ", "
        << m_schemas[id].size()
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
