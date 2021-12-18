include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/amqp)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)

set (reader-test-3-srcs
        main.cxx DeSerialiseMe.cxx DeSerialiseMe.h)


add_executable (reader-test-3 ${reader-test-3-srcs})

target_link_libraries (reader-test-3 amqp)

