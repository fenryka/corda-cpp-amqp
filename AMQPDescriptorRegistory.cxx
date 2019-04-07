
#include "AMQPDescriptorRegistory.h"

namespace amqp {
namespace internal {


    const long DESCRIPTOR_TOP_32BITS = 0xc562L << (32 + 16);

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

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
}


/******************************************************************************/

/**
 *
 */
namespace amqp {

    std::map<uint64_t, std::shared_ptr<AMQPDescriptor>>
    AMQPDescriptorRegistory = {
        {
            1L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<EnvelopeDescriptor> (
                    EnvelopeDescriptor ("ENVELOPE", internal::ENVELOPE))
        },
        {
            2L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<SchemaDescriptor> (
                    SchemaDescriptor ("SCHEMA", internal::SCHEMA))
        },
        {
            3L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<ObjectDescriptor> (
                    ObjectDescriptor ("OBJECT_DESCRIPTOR", internal::OBJECT))
        },
        {
            4L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<FieldDescriptor> (
                    FieldDescriptor ("FIELD", internal::FIELD))
        },
        {
            5L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<CompositeDescriptor> (
                    CompositeDescriptor ("COMPOSITE_TYPE", internal::COMPOSITE_TYPE))
        },
        {
            6L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<RestrictedDescriptor> (
                    RestrictedDescriptor ("RESTRICTED_TYPE", internal::RESTRICTED_TYPE))
        }
    };

    /*
    {  7L | DESCRIPTOR_TOP_32BITS, AMQPDescriptor ("CHOICE", 7) },
    {  8L | DESCRIPTOR_TOP_32BITS, AMQPDescriptor ("REFERENCED_OBJECT", 8) },
    {  9L | DESCRIPTOR_TOP_32BITS, AMQPDescriptor ("TRANSFORM_SCHEMA", 9) },
    { 10L | DESCRIPTOR_TOP_32BITS, AMQPDescriptor ("TRANSFORM_ELEMENT", 10) },
    { 11L | DESCRIPTOR_TOP_32BITS, AMQPDescriptor ("TRANSFORM_ELEMENT_KEY", 11) }
    */

}

/******************************************************************************/

