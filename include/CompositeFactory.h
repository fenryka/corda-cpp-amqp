#pragma once

/******************************************************************************/

#include <map>

#include "amqp/schema/Schema.h"
#include "amqp/schema/Composite.h"
#include "amqp/consumer/CompositeReader.h"

/******************************************************************************/

class CompositeFactory {
    private :
        using SchemaPtr = std::unique_ptr<amqp::internal::schema::Schema>;
        using CompositePtr = std::unique_ptr<amqp::internal::schema::Composite>;

        /**
         *
         */
        std::map<std::string, std::unique_ptr<amqp::CompositeReader>> m_readers;

    public :
        CompositeFactory() = default;

        void process (const SchemaPtr &);

    private :
        std::unique_ptr<amqp::CompositeReader> process (const CompositePtr &);
};

/******************************************************************************/

