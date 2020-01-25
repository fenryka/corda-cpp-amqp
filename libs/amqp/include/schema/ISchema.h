#pragma once

/******************************************************************************/

#include "corda-utils/include/types.h"

/******************************************************************************/

namespace amqp::schema {

    class ISchemaElement {
        public:
            virtual ~ISchemaElement() = default;
    };

    class ISchema {
        public :
            virtual const ISchemaElement & fromType (const std::string &) const = 0;
            virtual const ISchemaElement & fromDescriptor (const std::string &) const = 0;
    };

}

/******************************************************************************/
