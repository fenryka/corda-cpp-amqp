#pragma once

/******************************************************************************/

#include "corda-utils/include/types.h"

#include "schema/ISchema.h"
#include "serialiser/reader/IReader.h"

/******************************************************************************/

namespace amqp {

    class ICompositeFactory {
        public :
            ICompositeFactory() = default;

            virtual ~ICompositeFactory() = default;

            virtual void process (const amqp::schema::ISchema &) = 0;

            virtual const std::shared_ptr<amqp::serialiser::reader::IReader> byType (const std::string &) = 0;
            virtual const std::shared_ptr<amqp::serialiser::reader::IReader> byDescriptor (const std::string &) = 0;
    };

}

/******************************************************************************/

