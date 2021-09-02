#pragma once

/******************************************************************************/

#include "corda-utils/include/types.h"

/******************************************************************************/

namespace amqp::schema {

    class ISchemaElement {
        public:
            virtual ~ISchemaElement() = default;
    };

}

/******************************************************************************/

namespace amqp::schema {

    class ISchema {
        public :
            [[nodiscard]] virtual const ISchemaElement & fromType (const std::string &) const = 0;
            [[nodiscard]] virtual const ISchemaElement & fromDescriptor (const std::string &) const = 0;
    };

}

/******************************************************************************/
