include_directories (${BLOB-INSPECTOR_SOURCE_DIR}/libs)

link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/amqp)
link_directories (${BLOB-INSPECTOR_BINARY_DIR}/libs/proton-wrapper)

add_executable (data-dumper main.cxx DataDumper.cxx)

target_link_libraries (data-dumper amqp proton-wrapper qpid-proton)
