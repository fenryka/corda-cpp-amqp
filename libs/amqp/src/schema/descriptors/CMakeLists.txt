target_sources(amqp
        PRIVATE
            AMQPDescriptor.cxx
            AMQPDescriptors.cxx
            AMQPDescriptorRegistory.cxx
)

ADD_SUBDIRECTORY (corda-descriptors)

include_directories(corda-descriptors)