#pragma once

#include <amqp/src/serialiser/serialisers/reader/CompositeReader.h>
#include <amqp/src/serialiser/serialisers/writer/Writer.h>
#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/src/serialiser/Serialiser.h"
#include "amqp/src/serialiser/serialisers/CompositeSerialiser.h"

namespace amqp::internal::assembler {

    class SerialiserFactoryInternal : public amqp::assembler::SerialiserFactory {
        private :
            std::map<
                    std::string,
                    uPtr<
                            serialiser::serialisers::CompositeSerialiser<
                                    serialiser::reader::CompositeReader,
                                    serialiser::writer::Writer>>> m_serialisers;
        public :

            [[nodiscard]] uPtr<amqp::AMQPBlob>
            serialize(const amqp::serializable::Serializable &) const override;

            bool registerType (const amqp::serializable::Serializable &) override;
    };

}


uPtr<amqp::AMQPBlob>
amqp::internal::assembler::
SerialiserFactoryInternal::serialize(
        const amqp::serializable::Serializable &
) const {
    return nullptr;
}

bool
amqp::internal::assembler::
SerialiserFactoryInternal::registerType (
        const amqp::serializable::Serializable & clazz_)
{
    auto a = clazz_.build(*this);
    return true;
}
