#include "amqp/src/schema/descriptors/Descriptors.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    const int ENVELOPE              =  1;
    const int SCHEMA                =  2;
    const int OBJECT                =  3;
    const int FIELD                 =  4;
    const int COMPOSITE_TYPE        =  5;
    const int RESTRICTED_TYPE       =  6;
    const int CHOICE                =  7;
    const int REFERENCED_OBJECT     =  8;
    const int TRANSFORM_SCHEMA      =  9;
    const int TRANSFORM_ELEMENT     = 10;
    const int TRANSFORM_ELEMENT_KEY = 11;

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
