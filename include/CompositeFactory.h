#pragma once

/******************************************************************************/

#include <map>
#include <set>

#include "types.h"
#include "amqp/schema/Schema.h"
#include "amqp/schema/Envelope.h"
#include "amqp/schema/Composite.h"
#include "amqp/consumer/PropertyReader.h"
#include "amqp/consumer/CompositeReader.h"

/******************************************************************************/

class CompositeFactory {
    private :
        using SchemaPtr    = std::unique_ptr<amqp::internal::schema::Schema>;
        using CompositePtr = std::unique_ptr<amqp::internal::schema::Composite>;
        using EnvelopePtr  = std::unique_ptr<amqp::internal::schema::Envelope>;

        /**
         *
         */
        spStrMap_t<amqp::PropertyReader> m_propertyReaders;
        spStrMap_t<amqp::CompositeReader> m_compositeReadersByType;
        spStrMap_t<amqp::CompositeReader> m_compositeReadersByDescriptor;

    public :
        CompositeFactory() = default;

        void process (const SchemaPtr &);

        const std::shared_ptr<amqp::CompositeReader> byType (const std::string &);
        const std::shared_ptr<amqp::CompositeReader> byDescriptor (const std::string &);

    private :
        std::shared_ptr<amqp::CompositeReader>
        process__ (
                upStrMap_t<amqp::internal::schema::Composite>::const_iterator,
                std::set<std::string> &);
};

/******************************************************************************/

