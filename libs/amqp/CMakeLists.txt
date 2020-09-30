# Make it OK to convert relatvie paths when adding interface sources to targets
CMAKE_POLICY (SET CMP0076 NEW)

set (libName amqp)

include_directories (include)
include_directories (src/serialiser)
include_directories (src/schema)
include_directories (src/schema/descriptors)
include_directories (src/schema/described-types/field-types)
include_directories (src/schema/described-types)


set (amqp_sources
        src/AMQPBlob.cxx
        src/CordaBytes.cxx)

ADD_LIBRARY ( ${libName} SHARED ${amqp_sources})

TARGET_SOURCES ( ${libName} INTERFACE ${amqp_serialiser_interface} )

SET_TARGET_PROPERTIES (${libName} PROPERTIES VERSION ${PROJECT_VERSION})
SET_TARGET_PROPERTIES (${libName} PROPERTIES SOVERSION 1)

#
# So on Linux we don't need to add these static libraries to this dynamic library
# target buton MacOS it appears we do
#
if(APPLE)
    target_link_libraries (${libName} proton-wrapper qpid-proton)
endif()

ADD_SUBDIRECTORY (src)
