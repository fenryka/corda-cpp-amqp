#pragma once

/******************************************************************************/

#include <amqp/include/serialiser/ISerialiser.h>
#include "corda-utils/include/types.h"

#include "schema/ISchema.h"
#include "serialiser/reader/IReader.h"

/******************************************************************************/

namespace amqp {

    class ICompositeFactory {
        public :
            ICompositeFactory() = default;

            virtual ~ICompositeFactory() = default;

            virtual void process (const schema::ISchema &) = 0;

            virtual const std::shared_ptr<serialiser::ISerialiser> byType (const std::string &) = 0;
            virtual const std::shared_ptr<serialiser::ISerialiser> byDescriptor (const std::string &) = 0;
    };

}

/******************************************************************************/

