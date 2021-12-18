include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/amqp)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)
link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/corda-utils)

set (writer-test-11-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)

add_executable (writer-test-11 ${writer-test-11-srcs})

target_link_libraries (writer-test-11 amqp corda-utils)

