include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/amqp)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/corda-utils)

set (writer-test-08-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)


add_executable (writer-test-08 ${writer-test-08-srcs})

target_link_libraries (writer-test-08 amqp corda-utils)

