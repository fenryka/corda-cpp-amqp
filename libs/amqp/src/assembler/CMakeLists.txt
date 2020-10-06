target_sources(${libName}
    PRIVATE
        CompositeFactory.cxx
        SerialiserFactoryInternal.cxx
    PUBLIC
        SerialiserFactoryInternal.h
        CompositeFactory.h
)