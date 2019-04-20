include_directories (descriptors)
include_directories (schema)
include_directories (consumer)

set (amqp_sources
    descriptors/AMQPDescriptors.cxx
    descriptors/AMQPDescriptorRegistory.cxx
    schema/Schema.cxx
    schema/Field.cxx
    schema/Envelope.cxx
    schema/Composite.cxx
    schema/Descriptor.cxx
    consumer/Reader.cxx
    consumer/PropertyReader.cxx
    consumer/CompositeReader.cxx
    CompositeFactory.cxx
)

ADD_LIBRARY ( amqp ${amqp_sources} )

ADD_SUBDIRECTORY (test)
