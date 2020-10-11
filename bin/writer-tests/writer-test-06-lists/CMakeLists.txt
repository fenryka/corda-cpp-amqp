include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/amqp)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/corda-utils)

set (writer-test-06-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)


add_executable (writer-test-06 ${writer-test-06-srcs})

target_link_libraries (writer-test-06 amqp corda-utils)

