#include "AMQPDescriptorRegistory.h"
#include "AMQPDescriptors.h"

#include "Descriptors.h"

#include "corda-descriptors/FieldDescriptor.h"
#include "corda-descriptors/SchemaDescriptor.h"
#include "corda-descriptors/ObjectDescriptor.h"
#include "corda-descriptors/ChoiceDescriptor.h"
#include "corda-descriptors/EnvelopeDescriptor.h"
#include "corda-descriptors/CompositeDescriptor.h"
#include "corda-descriptors/RestrictedDescriptor.h"

#include <climits>

/******************************************************************************/

/**
 *
 */
namespace amqp::internal {

    std::map<uint64_t, std::shared_ptr<internal::schema::descriptors::AMQPDescriptor>>
    AMQPDescriptorRegistory = {
        {
            22UL,
            std::make_shared<internal::schema::descriptors::AMQPDescriptor> ("DESCRIBED", -1)
        },
        {
            schema::descriptors_longs::ENVELOPE | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::EnvelopeDescriptor> (
                    "ENVELOPE",
                    ::amqp::internal::schema::descriptors::ENVELOPE)
        },
        {
            schema::descriptors_longs::SCHEMA | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::SchemaDescriptor> (
                    "SCHEMA",
                    ::amqp::internal::schema::descriptors::SCHEMA)
        },
        {
            schema::descriptors_longs::OBJECT | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::ObjectDescriptor> (
                    "OBJECT_DESCRIPTOR",
                    ::amqp::internal::schema::descriptors::OBJECT)
        },
        {
            schema::descriptors_longs::FIELD | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::FieldDescriptor> (
                    "FIELD",
                    ::amqp::internal::schema::descriptors::FIELD)
        },
        {
            schema::descriptors_longs::COMPOSITE_TYPE | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::CompositeDescriptor> (
                    "COMPOSITE_TYPE",
                    ::amqp::internal::schema::descriptors::COMPOSITE_TYPE)
        },
        {
            schema::descriptors_longs::RESTRICTED_TYPE | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::RestrictedDescriptor> (
                    "RESTRICTED_TYPE",
                    ::amqp::internal::schema::descriptors::RESTRICTED_TYPE)
        },
        {
            schema::descriptors_longs::CHOICE | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::ChoiceDescriptor> (
                    "CHOICE",
                    ::amqp::internal::schema::descriptors::CHOICE)
        },
        {
            schema::descriptors_longs::REFERENCED_OBJECT | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::ReferencedObjectDescriptor> (
                    "REFERENCED_OBJECT",
                    ::amqp::internal::schema::descriptors::REFERENCED_OBJECT)
        },
        {
            schema::descriptors_longs::TRANSFORM_SCHEMA | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::TransformSchemaDescriptor> (
                    "TRANSFORM_SCHEMA",
                    ::amqp::internal::schema::descriptors::TRANSFORM_SCHEMA)
        },
        {
            schema::descriptors_longs::TRANSFORM_ELEMENT | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::TransformElementDescriptor> (
                    "TRANSFORM_ELEMENT",
                    ::amqp::internal::schema::descriptors::TRANSFORM_ELEMENT)
        },
        {
            schema::descriptors_longs::TRANSFORM_ELEMENT_KEY | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS,
            std::make_shared<internal::schema::descriptors::TransformElementKeyDescriptor> (
                    "TRANSFORM_ELEMENT_KEY",
                    ::amqp::internal::schema::descriptors::TRANSFORM_ELEMENT_KEY)
        }
    };
}

/******************************************************************************/

uint32_t
amqp::stripCorda (uint64_t id) {
    return static_cast<uint32_t>(id & (uint64_t)UINT_MAX);
}

/******************************************************************************/

std::string
amqp::describedToString (uint64_t val_) {
      switch (val_) {
          case (1UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "ENVELOPE";
          case (2UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "SCHEMA";
          case (3UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "OBJECT_DESCRIPTOR";
          case (4UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "FIELD";
          case (5UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "COMPOSITE_TYPE";
          case (6UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "RESTRICTED_TYPE";
          case (7UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "CHOICE";
          case (8UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "REFERENCED_OBJECT";
          case (9UL  | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "TRANSFORM_SCHEMA";
          case (10UL | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "TRANSFORM_ELEMENT";
          case (11UL | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS) : return "TRANSFORM_ELEMENT_KEY";
          default : return "UNKNOWN";
    }
}

/******************************************************************************/

std::string
amqp::describedToString (uint32_t val_) {
    return describedToString(val_ | ::amqp::internal::schema::descriptors::DESCRIPTOR_TOP_32BITS);
}

/******************************************************************************/
