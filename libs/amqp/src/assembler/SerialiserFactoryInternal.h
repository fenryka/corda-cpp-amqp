#pragma once

#include "amqp/src/serialiser/serialisers/reader/CompositeReader.h"
#include "amqp/src/serialiser/serialisers/writer/Writer.h"
#include "amqp/include/assembler/SerialiserFactory.h"
#include "amqp/src/serialiser/Serialiser.h"
#include "amqp/src/serialiser/serialisers/CompositeSerialiser.h"

namespace amqp::internal::assembler {

    class SerialiserFactoryInternal : public amqp::assembler::SerialiserFactory {
        private :

/*
        std::map<
                    std::string,
                    uPtr<
                            serialiser::serialisers::CompositeSerialiser<
                                    serialiser::reader::CompositeReader,
                                    serialiser::writer::Writer>>> m_serialisers;
                                    */
        public :
            void writeComposite (const amqp::serializable::Serializable &, ModifiableAMQPBlob &) const override;

            void writeInt(
                int,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &) const override;
    };

}

