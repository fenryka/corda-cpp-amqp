include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/corda-utils)
include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/proton-wrapper)
include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/amqp)
include_directories (${CORDA-AMQP-CPP_SOURCE_DIR}/libs/corda-custom-types)

link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/amqp)
link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/proton-wrapper)
link_directories (${CORDA-AMQP-CPP_BINARY_DIR}/libs/corda-custom-types)

set (exe-name blob-inspector)

set (blob-inspector-sources
        BlobInspector.cxx)

add_executable (${exe-name} main.cxx ${blob-inspector-sources})

target_link_libraries (${exe-name} amqp proton-wrapper qpid-proton corda-custom-types)

#
# Unit tests for the blob inspector. For this to work we also need to create
# a linkable library from the code here to link into our test.
#
add_library (blob-inspector-lib ${blob-inspector-sources} )
ADD_SUBDIRECTORY (test)
