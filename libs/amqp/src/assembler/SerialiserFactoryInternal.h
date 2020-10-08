#pragma once

#include "amqp/src/serialiser/serialisers/reader/CompositeReader.h"
#include "amqp/src/serialiser/serialisers/writer/Writer.h"
#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/src/serialiser/Serialiser.h"
#include "amqp/src/serialiser/serialisers/CompositeSerialiser.h"

/******************************************************************************/

#define writeCompositeM(__factory__, __type__, __parent__, __blob__) \
    __factory__.writeCompositePtr ( \
        javaTypeName<decltype (__type__)>(), __type__, #__type__, *this, __blob__);

/******************************************************************************/

namespace amqp::internal::assembler {

    class SerialiserFactoryInternal : public amqp::assembler::SerialiserFactory {
        public :
            [[nodiscard]] uPtr<ModifiableAMQPBlob> blob() const override;

            void writeComposite (
                const std::string & type,
                const amqp::serializable::Serializable &,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeCompositePtr (
                const std::string & type,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void startComposite (const amqp::serializable::Serializable &, ModifiableAMQPBlob &) const override;

            void writeInt(
                int,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeIntPtr(
                int *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeString(
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeStringPtr(
                std::string *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeLong(
                long,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;

            void writeBool(
                bool,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;
    };

}

/******************************************************************************/
