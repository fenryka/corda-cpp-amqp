target_sources(${libName}
    PRIVATE
        ISerialiser.cxx
    PUBLIC
        Serialiser.h
        SerialiserFactoryInternal.h
)

ADD_SUBDIRECTORY (serialisers)

INCLUDE_DIRECTORIES(src/schema)