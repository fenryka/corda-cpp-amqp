target_sources(amqp
    PRIVATE
        ISerialiser.cxx
    PUBLIC
        Serialiser.h
        SerialiserFactory.h
)

ADD_SUBDIRECTORY (serialisers)