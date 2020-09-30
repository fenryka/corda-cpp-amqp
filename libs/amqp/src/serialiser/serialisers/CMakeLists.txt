target_sources(amqp
    PRIVATE
        CompositeSerialiser.h
        RestrictedSerialiser.h
        PropertySerialiser.h
)

ADD_SUBDIRECTORY (writer)
ADD_SUBDIRECTORY (reader)
ADD_SUBDIRECTORY (property-serialisers)
ADD_SUBDIRECTORY (restricted-serialisers)