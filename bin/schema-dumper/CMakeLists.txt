include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs)
include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/amqp)
include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs/corda-utils)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/proton-wrapper)

add_executable (schema-dumper main.cxx SchemaDumper.cxx)

target_link_libraries (schema-dumper amqp proton-wrapper qpid-proton)
