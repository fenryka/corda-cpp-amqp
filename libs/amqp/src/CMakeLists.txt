ADD_SUBDIRECTORY (test)
ADD_SUBDIRECTORY (assembler)
ADD_SUBDIRECTORY (schema)
ADD_SUBDIRECTORY (serialiser)
ADD_SUBDIRECTORY (serializable)

TARGET_SOURCES(${libName}
        PRIVATE
            AMQPBlob.cxx
            CordaBytes.cxx
            ModifiableAMQPBlob.cxx)



