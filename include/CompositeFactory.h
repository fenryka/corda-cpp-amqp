#pragma once

/******************************************************************************/

#include <map>

#include "amqp/schema/Schema.h"
#include "amqp/schema/Envelope.h"
#include "amqp/schema/Composite.h"
#include "amqp/consumer/PropertyReader.h"
#include "amqp/consumer/CompositeReader.h"

/******************************************************************************/

template<typename T>
using StrPtrMap = std::map<std::string, std::shared_ptr<T>>;

/******************************************************************************/

class CompositeFactory {
    private :
        using SchemaPtr = std::unique_ptr<amqp::internal::schema::Schema>;
        using CompositePtr = std::unique_ptr<amqp::internal::schema::Composite>;
        using EnvelopePtr = std::unique_ptr<amqp::internal::schema::Envelope>;

        /**
         *
         */
        StrPtrMap<amqp::PropertyReader> m_propertyReaders;


        StrPtrMap<amqp::CompositeReader> m_compositeReadersByType;
        StrPtrMap<amqp::CompositeReader> m_compositeReadersByDescriptor;

    public :
        CompositeFactory() = default;

        void process (const SchemaPtr &);

        const std::shared_ptr<amqp::CompositeReader> byType (const std::string &);
        const std::shared_ptr<amqp::CompositeReader> byDescriptor (const std::string &);

    private :
        std::shared_ptr<amqp::CompositeReader> process (const CompositePtr &);
};

/******************************************************************************/

