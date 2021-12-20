set (exe-name proton-wrapper-link-test)

set (sources
        proton-wrapper-link-test.cxx)

FIND_LIBRARY(proton-wrapper REQUIRED)

add_executable (${exe-name} ${sources})

target_link_libraries (${exe-name} proton-wrapper qpid-proton)

