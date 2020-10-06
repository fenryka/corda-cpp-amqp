#pragma once

#include "amqp/include/ModifiableAMQPBlob.h"

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"
#include "amqp/src/schema/descriptors/corda-descriptors/FieldDescriptor.h"
#include "amqp/src/serialiser/Serialiser.h"
#include "amqp/include/serializable/Serializable.h"

#include "amqp/src/serialiser/serialisers/property-serialisers/IntPropertySerialiserBase.h"
#include "amqp/src/serialiser/serialisers/property-serialisers/StringPropertySerialiserBase.h"

#include <map>

/******************************************************************************
 *
 * class amqp::ModifiableAMQPBlob
 *
 ******************************************************************************/

namespace amqp::internal {

    class ModifiableAMQPBlobImpl : public amqp::ModifiableAMQPBlob {
        private :
            pn_data_t * m_payload;
            std::map<std::pair<std::string, std::string>, std::vector<pn_data_t *>> m_schemas;

        public :
            ModifiableAMQPBlobImpl();

            void startComposite (const amqp::serializable::Serializable &);
            void writeComposite (const amqp::serializable::Serializable &);

            template<typename T>
            void writePrimitive(
                const T &,
                const std::string &,
                const amqp::serializable::Serializable &);

        [[nodiscard]] uPtr<AMQPBlob> toBlob() const override;
    };

}

/******************************************************************************/

template<typename T>
void
amqp::internal::
ModifiableAMQPBlobImpl::writePrimitive (
    const T & propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_)
{
    DBG (__FUNCTION__ << "::" << propertyName_ << "::" << propertyValue_ << std::endl); // NOLINT

    auto key = std::make_pair (clazz_.name(), clazz_.fingerprint());

    assert (m_schemas.find (key) != m_schemas.end());

    DBG ("FOUND IT" << std::endl); // NOLINT

    m_schemas[key].emplace_back (
        internal::schema::descriptors::FieldDescriptor::makeProton(
            propertyName_,
            amqp::internal::serialiser::PrimToSerialiser<T>::serialiser::m_type,
            {}));

    amqp::internal::serialiser::PrimToSerialiser<T>::put (propertyValue_, m_payload);
}

/******************************************************************************/
