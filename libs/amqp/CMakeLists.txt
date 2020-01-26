# Make it OK to convert relatvie paths when adding interface sources to targets
CMAKE_POLICY (SET CMP0076 NEW)

set (libName amqp)

include_directories (include)
include_directories (src/serialiser/reader)
include_directories (src/schema)
include_directories (src/schema/descriptors)
include_directories (src/schema/described-types/field-types)
include_directories (src/schema/described-types)

set (amqp_schema_sources
        src/schema/descriptors/AMQPDescriptor.cxx
        src/schema/descriptors/AMQPDescriptors.cxx
        src/schema/descriptors/AMQPDescriptorRegistory.cxx
        src/schema/descriptors/corda-descriptors/FieldDescriptor.cxx
        src/schema/descriptors/corda-descriptors/SchemaDescriptor.cxx
        src/schema/descriptors/corda-descriptors/ObjectDescriptor.cxx
        src/schema/descriptors/corda-descriptors/ChoiceDescriptor.cxx
        src/schema/descriptors/corda-descriptors/EnvelopeDescriptor.cxx
        src/schema/descriptors/corda-descriptors/CompositeDescriptor.cxx
        src/schema/descriptors/corda-descriptors/RestrictedDescriptor.cxx
        src/schema/described-types/field-types/Field.cxx
        src/schema/described-types/field-types/PrimitiveField.cxx
        src/schema/described-types/field-types/CompositeField.cxx
        src/schema/described-types/field-types/RestrictedField.cxx
        src/schema/described-types/field-types/ArrayField.cxx
        src/schema/described-types/Schema.cxx
        src/schema/described-types/Choice.cxx
        src/schema/described-types/Envelope.cxx
        src/schema/described-types/Composite.cxx
        src/schema/described-types/Descriptor.cxx
        src/schema/restricted-types/Restricted.cxx
        src/schema/restricted-types/List.cxx
        src/schema/restricted-types/Enum.cxx
        src/schema/restricted-types/Map.cxx
        src/schema/restricted-types/Array.cxx
        src/schema/AMQPTypeNotation.cxx
        src/schema/Descriptors.cxx
        src/schema/SchemaUtils.cxx
        )

set (amqp_assembler_sources
        src/assembler/CompositeFactory.cxx
     )

set (amqp_serialiser_sources
        )

set (amqp_reader_sources
        src/serialiser/reader/Reader.cxx
        src/serialiser/reader/CompositeReader.cxx
        src/serialiser/reader/property-readers/IntPropertyReader.cxx
        src/serialiser/reader/property-readers/LongPropertyReader.cxx
        src/serialiser/reader/property-readers/BoolPropertyReader.cxx
        src/serialiser/reader/property-readers/DoublePropertyReader.cxx
        src/serialiser/reader/property-readers/StringPropertyReader.cxx
        src/serialiser/reader/restricted-readers/MapReader.cxx
        src/serialiser/reader/restricted-readers/ListReader.cxx
        src/serialiser/reader/restricted-readers/ArrayReader.cxx
        src/serialiser/reader/restricted-readers/EnumReader.cxx
        )

set (amqp_serialiser_interface
        src/serialiser/Serialiser.h
        src/serialiser/serialisers/SerialiserFactory.h
        src/serialiser/serialisers/CompositeSerialiser.h
        src/serialiser/serialisers/restricted-serialisers/RestrictedSerialiser.h
        src/serialiser/serialisers/restricted-serialisers/ListSerialiser.h
        src/serialiser/serialisers/restricted-serialisers/EnumSerialiser.h
        src/serialiser/serialisers/restricted-serialisers/MapSerialiser.h
        src/serialiser/serialisers/property-serialisers/PropertySerialiser.h
        src/serialiser/serialisers/property-serialisers/BoolPropertySerialiser.h
        src/serialiser/serialisers/property-serialisers/DoublePropertySerialiser.h
        src/serialiser/serialisers/property-serialisers/IntPropertySerialiser.h
        src/serialiser/serialisers/property-serialisers/LongPropertySerialiser.h
        src/serialiser/serialisers/property-serialisers/StringPropertySerialiser.h
        )

set (amqp_sources
        src/AMQPBlob.cxx
        src/CordaBytes.cxx)

ADD_LIBRARY ( ${libName} SHARED ${amqp_sources} ${amqp_serialiser_sources} ${amqp_reader_sources} ${amqp_schema_sources} ${amqp_assembler_sources} )

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
