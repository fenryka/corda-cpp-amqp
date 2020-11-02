set (EXE "serializable-tests")

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)

set (sources
        main.cxx
        SerializableVectorTests.cxx
        )

add_executable (${EXE} ${sources})

target_link_libraries (${EXE} gtest amqp corda-utils)

