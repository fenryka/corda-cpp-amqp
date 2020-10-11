set (EXE "corda-utils-test")

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/corda-utils)

set (sources
        main.cxx
        TypeTests.cxx
)

add_executable (${EXE} ${sources})

target_link_libraries (${EXE} gtest corda-utils)

