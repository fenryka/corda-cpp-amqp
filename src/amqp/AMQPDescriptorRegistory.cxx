
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
        },
        {
            7L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<ChoiceDescriptor> (
                    ChoiceDescriptor ("CHOICE", internal::CHOICE))
        },
        {
            8L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<ReferencedObjectDescriptor> (
                    ReferencedObjectDescriptor ("REFERENCED_OBJECT", internal::REFERENCED_OBJECT))
        },
        {
            9L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<TransformSchemaDescriptor> (
                    TransformSchemaDescriptor ("TRANSFORM_SCHEMA", internal::TRANSFORM_SCHEMA))
        },
        {
            10L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<TransformElementDescriptor> (
                TransformElementDescriptor ("TRANSFORM_ELEMENT", internal::TRANSFORM_ELEMENT))
        },
        {
            11L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<TransformElementKeyDescriptor> (
                TransformElementKeyDescriptor ("TRANSFORM_ELEMENT_KEY", internal::TRANSFORM_ELEMENT_KEY))
        }
    };


}

/******************************************************************************/

