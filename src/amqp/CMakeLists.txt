include_directories (descriptors)
include_directories (schema)

set (amqp_sources
    descriptors/AMQPDescriptors.cxx
    descriptors/AMQPDescriptorRegistory.cxx
    schema/Envelope.cxx
    schema/Field.cxx
)

ADD_LIBRARY ( amqp ${amqp_sources} )

