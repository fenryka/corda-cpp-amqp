#pragma once

#include <amqp/src/ModifiableAMQPBlobImpl.h>
#include "amqp/src/serialiser/serialisers/reader/CompositeReader.h"
#include "amqp/src/serialiser/serialisers/writer/Writer.h"
#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/src/serialiser/Serialiser.h"
#include "amqp/src/serialiser/serialisers/CompositeSerialiser.h"

/******************************************************************************/

namespace amqp::internal::assembler {

    using Serializable = amqp::serializable::Serializable;

    class SerialiserFactoryInternal : public amqp::assembler::SerialiserFactory {
        public :
            [[nodiscard]] uPtr<ModifiableAMQPBlob> blob() const override;

            void writeComposite_ (
                const std::string &,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeCompositeSingle_ (
                const std::string &,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeRestricted_ (
                const std::string &,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void startComposite (const amqp::serializable::Serializable &, ModifiableAMQPBlob &) const override;
            void startRestricted (const amqp::serializable::Serializable &, ModifiableAMQPBlob &) const override;

    };

}

/******************************************************************************/
