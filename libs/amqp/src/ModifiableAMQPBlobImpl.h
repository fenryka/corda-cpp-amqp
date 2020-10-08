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

            std::map<
                std::pair<std::string, std::string>,
                std::map<
                    std::string,
                    pn_data_t *>> m_schemas;

        public :
            ModifiableAMQPBlobImpl();

            static std::pair<std::string, std::string> key (const amqp::serializable::Serializable &);

            void startComposite (const amqp::serializable::Serializable &);

            void writeComposite (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &,
                const amqp::serializable::Serializable &);

            template<typename T>
            void writePrimitive(
                T,
                const std::string &,
                const amqp::serializable::Serializable &);

            void writeNull (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &);

            [[nodiscard]] uPtr<AMQPBlob> toBlob() const override;

            void dump() const;
    };

}

/******************************************************************************/

template<typename T>
void
amqp::internal::
ModifiableAMQPBlobImpl::writePrimitive (
    T propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_)
{
    DBG (__FUNCTION__
        << "::"
        << propertyName_
        << "::"
        << propertyValue_ << std::endl); // NOLINT

    auto id = key (clazz_);

    assert (m_schemas.find (id) != m_schemas.end());

    DBG ("FOUND IT" << std::endl); // NOLINT

    std::string type = serialiser::PrimToSerialiser<
        std::remove_const_t<T>
    >::serialiser::m_type;

    if (m_schemas[id].find (propertyName_) == m_schemas[id].end()) {
        m_schemas[id][propertyName_] =
            internal::schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                type,
                {},
                "", "",
                std::is_pointer_v<T>,
                false);
    }

    DBG ("WRITE IT" << std::endl); // NOLINT

    serialiser::PrimToSerialiser<
        std::remove_const_t<T>
    >::put (propertyValue_, m_payload);
}

/******************************************************************************/
