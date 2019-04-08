include_directories (descriptors)
include_directories (described)


set (amqp_sources
    descriptors/AMQPDescriptors.cxx
    descriptors/AMQPDescriptorRegistory.cxx
    described/Envelope.cxx
)

ADD_LIBRARY ( amqp ${amqp_sources} )

