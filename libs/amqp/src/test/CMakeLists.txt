set (EXE "amqp-test")

set (amqp-test-sources
        main.cxx
        Map.cxx
        Pair.cxx
        List.cxx
        Single.cxx
        TestUtils.cxx
        RestrictedDescriptor.cxx
        OrderedTypeNotationTest.cxx
        SchemaUtils.cxx
        RoundTripTests.cxx
        RoundTripListTests.cxx)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)

add_executable (${EXE} ${amqp-test-sources})

target_link_libraries (${EXE} gtest amqp)

if (UNIX)
    target_link_libraries (${EXE} pthread qpid-proton proton-wrapper)
endif (UNIX)
