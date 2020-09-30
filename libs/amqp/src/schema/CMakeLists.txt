target_sources(${libName}
        PRIVATE
            AMQPTypeNotation.cxx
            Descriptors.cxx
            SchemaUtils.cxx
        PUBLIC
)

INCLUDE_DIRECTORIES(descriptors)

ADD_SUBDIRECTORY (restricted-types)
ADD_SUBDIRECTORY (described-types)
ADD_SUBDIRECTORY (descriptors)