include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/amqp)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)

set (reader-test-05-srcs
        main.cxx DeSerialiseMe.cxx DeSerialiseMe.h)


add_executable (reader-test-05 ${reader-test-05-srcs})

target_link_libraries (reader-test-05 amqp)

