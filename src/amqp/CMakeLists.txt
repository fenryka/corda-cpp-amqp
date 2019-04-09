include_directories (descriptors)
include_directories (schema)

set (amqp_sources
    descriptors/AMQPDescriptors.cxx
    descriptors/AMQPDescriptorRegistory.cxx
    schema/Envelope.cxx
    schema/Schema.cxx
    schema/Composite.cxx
    schema/Descriptor.cxx
)

ADD_LIBRARY ( amqp ${amqp_sources} )

