#pragma once

/******************************************************************************/

#include <cstdint>

/******************************************************************************/

/**
 * R3 AMQP assigned enterprise number
 *
 * see [here](https://www.iana.org/assignments/enterprise-numbers/enterprise-numbers)
 *
 * Repeated here for brevity:
 *   50530 - R3 - Mike Hearn - mike&r3.com
 */
namespace amqp::internal::schema::descriptors {

    constexpr uint64_t DESCRIPTOR_TOP_32BITS = 0xc562UL << (unsigned int)(32 + 16);

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    extern const unsigned int ENVELOPE;
    extern const unsigned int SCHEMA;
    extern const unsigned int OBJECT;
    extern const unsigned int FIELD;
    extern const unsigned int COMPOSITE_TYPE;
    extern const unsigned int RESTRICTED_TYPE;
    extern const unsigned int CHOICE;
    extern const unsigned int REFERENCED_OBJECT;
    extern const unsigned int TRANSFORM_SCHEMA;
    extern const unsigned int TRANSFORM_ELEMENT;
    extern const unsigned int TRANSFORM_ELEMENT_KEY;

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors_longs {

    extern const unsigned long ENVELOPE;
    extern const unsigned long SCHEMA;
    extern const unsigned long OBJECT;
    extern const unsigned long FIELD;
    extern const unsigned long COMPOSITE_TYPE;
    extern const unsigned long RESTRICTED_TYPE;
    extern const unsigned long CHOICE;
    extern const unsigned long REFERENCED_OBJECT;
    extern const unsigned long TRANSFORM_SCHEMA;
    extern const unsigned long TRANSFORM_ELEMENT;
    extern const unsigned long TRANSFORM_ELEMENT_KEY;

}

/******************************************************************************/
