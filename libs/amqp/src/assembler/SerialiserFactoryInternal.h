#pragma once

#include "amqp/src/serialiser/serialisers/reader/CompositeReader.h"
#include "amqp/src/serialiser/serialisers/writer/Writer.h"
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


            void writeInt(int, const std::string &, ModifiableAMQPBlob &) const override;
    };

}


uPtr<amqp::AMQPBlob>
amqp::internal::assembler::
SerialiserFactoryInternal::serialize(
        const amqp::serializable::Serializable &
) const {
    return nullptr;
}

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeInt(
    int val_,
    const std::string & name,
    amqp::ModifiableAMQPBlob & blob_
) const {

}

