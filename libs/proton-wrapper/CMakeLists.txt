set (libname proton-wrapper)

set (proton_sources
        src/proton_wrapper.cxx
)

ADD_LIBRARY (${libname} SHARED ${proton_sources})

SET_TARGET_PROPERTIES (${libName} PROPERTIES VERSION ${PROJECT_VERSION})
SET_TARGET_PROPERTIES (${libName} PROPERTIES SOVERSION 1)
SET_TARGET_PROPERTIES (${libName} PROPERTIES PUBLIC_HEADER include/proton_wrapper.h)

target_link_libraries (${libname} qpid-proton)