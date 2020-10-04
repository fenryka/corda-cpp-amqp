target_sources (${libName}
        PRIVATE
        ../src/ModifiableAMQPBlob.cxx
        PUBLIC
            AMQPBlob.h
            AMQPHeader.h
            AMQPSectionId.h
        )

ADD_SUBDIRECTORY (serializable)

