set (EXE "serializable-tests")

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)

set (sources
        main.cxx
        SerializableVectorTests.cxx
        )

set (libs
        gtest
        amqp
        corda-utils
        proton-wrapper
        qpid-proton)

# add posix threading lib for gtest on linux
IF (UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    set (THREAD_LIB Threads::Threads)
ENDIF()

add_executable (${EXE} ${sources})

target_link_libraries (${EXE} ${libs} ${THREAD_LIB})

