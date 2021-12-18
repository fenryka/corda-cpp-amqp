#include "amqp/src/schema/descriptors/Descriptors.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    const unsigned int ENVELOPE              =  1;
    const unsigned int SCHEMA                =  2;
    const unsigned int OBJECT                =  3;
    const unsigned int FIELD                 =  4;
    const unsigned int COMPOSITE_TYPE        =  5;
    const unsigned int RESTRICTED_TYPE       =  6;
    const unsigned int CHOICE                =  7;
    const unsigned int REFERENCED_OBJECT     =  8;
    const unsigned int TRANSFORM_SCHEMA      =  9;
    const unsigned int TRANSFORM_ELEMENT     = 10;
    const unsigned int TRANSFORM_ELEMENT_KEY = 11;

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors_longs {

    const unsigned long ENVELOPE              =  1;
    const unsigned long SCHEMA                =  2;
    const unsigned long OBJECT                =  3;
    const unsigned long FIELD                 =  4;
    const unsigned long COMPOSITE_TYPE        =  5;
    const unsigned long RESTRICTED_TYPE       =  6;
    const unsigned long CHOICE                =  7;
    const unsigned long REFERENCED_OBJECT     =  8;
    const unsigned long TRANSFORM_SCHEMA      =  9;
    const unsigned long TRANSFORM_ELEMENT     = 10;
    const unsigned long TRANSFORM_ELEMENT_KEY = 11;

}
