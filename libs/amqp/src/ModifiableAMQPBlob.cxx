#include "ModifiableAMQPBlob.h"

#include <proton/codec.h>

#include "amqp/include/serializable/Serializable.h"

amqp::
ModifiableAMQPBlob::ModifiableAMQPBlob()
        : m_payload (pn_data (0))
{

}

void
amqp::
ModifiableAMQPBlob::startComposite (
        const amqp::serializable::Serializable & composite_
) {

    auto it = m_schemas.find (composite_.fingerprint());
    if (it == m_schemas.end()) {
        m_schemas[composite_.fingerprint()] = pn_data (0);
    }

    auto schema = m_schemas[composite_.fingerprint()];

    pn_data_put_described(schema);
    pn_data_enter(schema);
    pn_data_put_symbol (schema, pn_bytes ( composite_.fingerprint().size(), composite_.fingerprint().data()));
    pn_data_put_list (schema);
    pn_data_enter (schema);

    pn_data_put_described (m_payload);
    pn_data_enter (m_payload);
    pn_data_put_symbol (m_payload, pn_bytes ( composite_.fingerprint().size(), composite_.fingerprint().data()));
    pn_data_put_list (m_payload);
    pn_data_enter (m_payload);
}

void
amqp::
ModifiableAMQPBlob::writeInt(
        int propertyValue_,
        const std::string & propertyName_,
        const amqp::serializable::Serializable & clazz_)
{
//    pn_data_put_described(m_schemas[clazz_.fingerprint()]
}
