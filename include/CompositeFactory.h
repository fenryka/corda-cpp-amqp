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

        spStrMap_t<amqp::Reader> m_readersByType;
        spStrMap_t<amqp::Reader> m_readersByDescriptor;

    public :
        CompositeFactory() = default;

        void process (const SchemaPtr &);

        const std::shared_ptr<amqp::Reader> byType (const std::string &);
        const std::shared_ptr<amqp::Reader> byDescriptor (const std::string &);

    private :
        std::shared_ptr<amqp::Reader>
        process (
                upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator,
                std::set<std::string> &);

        std::shared_ptr<amqp::Reader>
        processComposite (
                upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator,
                std::set<std::string> &);

        std::shared_ptr<amqp::Reader>
        processRestricted (
            upStrMap_t<amqp::internal::schema::AMQPTypeNotation>::const_iterator,
            std::set<std::string> &);
};

/******************************************************************************/

