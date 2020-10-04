#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"
#include "corda-utils/include/types.h"

/******************************************************************************/

namespace amqp::schema {

    class ISchema;

}

/******************************************************************************/

namespace amqp {

    class ICompositeFactory {
        public :
            ICompositeFactory() = default;

            virtual ~ICompositeFactory() = default;

            virtual void process (const schema::ISchema &) = 0;

            virtual const sPtr<serialiser::ISerialiser> byType (
                    const std::string &) = 0;

            virtual const sPtr<serialiser::ISerialiser> byDescriptor (
                    const std::string &) = 0;
    };

}

/******************************************************************************/

