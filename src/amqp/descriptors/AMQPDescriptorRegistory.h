#pragma once

/******************************************************************************/

#include <map>
#include <memory>

/******************************************************************************/

#include "amqp/AMQPDescriptor.h"

/******************************************************************************/

/**
 * R3 AMQP assigned enterprise number
 *
 * see [here](https://www.iana.org/assignments/enterprise-numbers/enterprise-numbers)
 *
 * Repeated here for brevity:
 *   50530 - R3 - Mike Hearn - mike&r3.com
 */
namespace amqp {
namespace internal {

    extern const long DESCRIPTOR_TOP_32BITS;

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    extern const int ENVELOPE;
    extern const int SCHEMA;
    extern const int OBJECT_DESCRIPTOR;
    extern const int FIELD;
    extern const int COMPOSITE_TYPE;
    extern const int RESTRICTED_TYPE;
    extern const int CHOICE;
    extern const int REFERENCED_OBJECT;
    extern const int TRANSFORM_SCHEMA;
    extern const int TRANSFORM_ELEMENT;
    extern const int TRANSFORM_ELEMENT_KEY;

}
}


/******************************************************************************/

/**
 *
 */
namespace amqp {

    extern std::map<uint64_t, std::shared_ptr<internal::AMQPDescriptor>> AMQPDescriptorRegistory;

}

/******************************************************************************/

