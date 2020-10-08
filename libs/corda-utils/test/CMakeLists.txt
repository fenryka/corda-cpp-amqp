set (EXE "corda-utils-test")

set (sources
        main.cxx
        TypeTests.cxx
)

add_executable (${EXE} ${sources})

target_link_libraries (${EXE} gtest)

