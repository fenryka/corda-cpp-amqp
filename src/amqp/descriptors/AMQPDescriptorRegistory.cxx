#include "AMQPDescriptorRegistory.h"
#include "AMQPDescriptors.h"

/******************************************************************************/

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

    std::map<uint64_t, std::shared_ptr<internal::AMQPDescriptor>>
    AMQPDescriptorRegistory = {
        {
            1L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::EnvelopeDescriptor> (
                    internal::EnvelopeDescriptor ("ENVELOPE", internal::ENVELOPE))
        },
        {
            2L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::SchemaDescriptor> (
                    internal::SchemaDescriptor ("SCHEMA", internal::SCHEMA))
        },
        {
            3L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::ObjectDescriptor> (
                    internal::ObjectDescriptor ("OBJECT_DESCRIPTOR", internal::OBJECT))
        },
        {
            4L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::FieldDescriptor> (
                    internal::FieldDescriptor ("FIELD", internal::FIELD))
        },
        {
            5L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::CompositeDescriptor> (
                    internal::CompositeDescriptor (
                        "COMPOSITE_TYPE",
                        internal::COMPOSITE_TYPE)
                    )
        },
        {
            6L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::RestrictedDescriptor> (
                    internal::RestrictedDescriptor (
                        "RESTRICTED_TYPE",
                        internal::RESTRICTED_TYPE)
                    )
        },
        {
            7L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::ChoiceDescriptor> (
                    internal::ChoiceDescriptor (
                        "CHOICE",
                        internal::CHOICE)
                    )
        },
        {
            8L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::ReferencedObjectDescriptor> (
                    internal::ReferencedObjectDescriptor (
                        "REFERENCED_OBJECT",
                        internal::REFERENCED_OBJECT)
                    )
        },
        {
            9L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::TransformSchemaDescriptor> (
                    internal::TransformSchemaDescriptor (
                        "TRANSFORM_SCHEMA",
                        internal::TRANSFORM_SCHEMA)
                    )
        },
        {
            10L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::TransformElementDescriptor> (
                internal::TransformElementDescriptor (
                    "TRANSFORM_ELEMENT",
                    internal::TRANSFORM_ELEMENT)
                )
        },
        {
            11L | internal::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::TransformElementKeyDescriptor> (
                internal::TransformElementKeyDescriptor (
                    "TRANSFORM_ELEMENT_KEY",
                    internal::TRANSFORM_ELEMENT_KEY)
                )
        }
    };
}

/******************************************************************************/

