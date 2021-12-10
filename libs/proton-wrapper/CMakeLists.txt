set (libname proton-wrapper)

set (proton_sources
        src/proton_wrapper.cxx
)


ADD_LIBRARY (${libname} SHARED ${proton_sources})
target_link_libraries (${libname} qpid-proton)