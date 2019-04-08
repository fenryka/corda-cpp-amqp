set (amqp_sources
    AMQPDescriptor.cxx
    AMQPDescriptorRegistory.cxx
    Envelope.cxx
)

ADD_LIBRARY ( amqp ${amqp_sources} )

