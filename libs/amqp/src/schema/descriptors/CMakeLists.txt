target_sources(${libName}
        PRIVATE
            AMQPDescriptor.cxx
            AMQPDescriptors.cxx
            AMQPDescriptorRegistory.cxx
)

ADD_SUBDIRECTORY (corda-descriptors)

include_directories(corda-descriptors)