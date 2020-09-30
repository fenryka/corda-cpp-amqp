target_sources(amqp
    PRIVATE
        Schema.cxx
        Choice.cxx
        Envelope.cxx
        Composite.cxx
        Descriptor.cxx
)

ADD_SUBDIRECTORY (field-types)