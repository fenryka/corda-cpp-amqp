include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/amqp)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)
link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/corda-utils)

set (writer-test-09-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)


add_executable (writer-test-09 ${writer-test-09-srcs})

target_link_libraries (writer-test-09 amqp corda-utils)

