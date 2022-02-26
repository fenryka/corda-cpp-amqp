include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/amqp)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)

set (reader-test-06-srcs
        main.cxx
        DeSerialiseMe.cxx
        DeSerialiseMe.h)

add_executable (reader-test-06 ${reader-test-06-srcs})

target_link_libraries (reader-test-06 amqp)

