#pragma once

/******************************************************************************/

#include <map>
#include <set>
#include <memory>
#include <amqp/src/serialiser/Serialiser.h>

#include "corda-utils/include/types.h"

#include "amqp/include/assembler/ICompositeFactory.h"
#include "amqp/include/serialiser/ISerialiser.h"

#include "amqp/src/serialiser/serialisers/reader/CompositeReader.h"

#include "amqp/src/schema/described-types/Schema.h"
#include "amqp/src/schema/described-types/Envelope.h"
#include "amqp/src/schema/described-types/Composite.h"
#include "amqp/src/schema/restricted-types/Map.h"
#include "amqp/src/schema/restricted-types/Array.h"
#include "amqp/src/schema/restricted-types/List.h"
#include "amqp/src/schema/restricted-types/Enum.h"

/******************************************************************************/

namespace amqp::internal::assembler {

    class CompositeFactory : public ICompositeFactory {
        private :
            using CompositePtr = uPtr<schema::Composite>;
            using EnvelopePtr  = uPtr<schema::Envelope>;

            spStrMap_t<amqp::serialiser::ISerialiser> m_serialisersByType;
            spStrMap_t<amqp::serialiser::ISerialiser> m_serialisersByDescriptor;

        public :
            CompositeFactory() = default;

            void process (const amqp::schema::ISchema &) override;

            const sPtr<amqp::serialiser::ISerialiser> byType (
                    const std::string &) override;

            const sPtr<amqp::serialiser::ISerialiser> byDescriptor (
                    const std::string &) override;

        private :
            sPtr<amqp::serialiser::ISerialiser> process (
                    const schema::AMQPTypeNotation &);

            sPtr<amqp::serialiser::ISerialiser> processComposite (
                    const schema::AMQPTypeNotation &);

            sPtr<amqp::serialiser::ISerialiser> processRestricted (
                    const schema::AMQPTypeNotation &);

            sPtr<amqp::serialiser::ISerialiser> processList (
                    const schema::List &);

            sPtr<amqp::serialiser::ISerialiser> processEnum (
                    const schema::Enum &);

            sPtr<amqp::serialiser::ISerialiser> processMap (
                    const schema::Map &);

            sPtr<amqp::serialiser::ISerialiser> processArray (
                    const schema::Array &);

            decltype(m_serialisersByType)::mapped_type
            fetchReaderForRestricted (const std::string &);
    };

}

/******************************************************************************/

