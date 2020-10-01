#include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/corda-utils)
#include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/proton-wrapper)
include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/amqp)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
#link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/proton-wrapper)

set (writer-test-1-srcs
        main.cxx SerialiseMe.cxx SerialiseMe.h)


add_executable (writer-test-1 ${writer-test-1-srcs})

target_link_libraries (writer-test-1 amqp)

#
# Unit tests for the blob inspector. For this to work we also need to create
# a linkable library from the code here to link into our test.
#
#add_library (blob-inspector-lib ${blob-inspector-sources} )
