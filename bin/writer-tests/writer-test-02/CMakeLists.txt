include_directories (${CORDA-CPP-AMQP_SOURCE_DIR}/libs/amqp)

link_directories (${CORDA-CPP-AMQP_BINARY_DIR}/libs/amqp)

set (writer-test-2-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)


add_executable (writer-test-2 ${writer-test-2-srcs})

target_link_libraries (writer-test-2 amqp)

