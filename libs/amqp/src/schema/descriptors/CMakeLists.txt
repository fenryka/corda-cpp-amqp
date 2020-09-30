target_sources(amqp
        PRIVATE
            AMQPDescriptor.cxx
            AMQPDescriptors.cxx
            AMQPDescriptorRegistory.cxx
)

ADD_SUBDIRECTORY (corda-descriptors)