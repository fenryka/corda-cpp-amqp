set (EXE "corda-utils-test")

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/corda-utils)

set (sources
        main.cxx
        TypeTests.cxx
)

set (libs
        gtest
        corda-utils)

# gtest requires linking against the posix threading libs on linux... but not on
# apple
IF (UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    set (THREAD_LIB Threads::Threads)
ENDIF()

add_executable (${EXE} ${sources})

target_link_libraries (${EXE} ${libs} ${THREAD_LIB})


