set (libName corda-utils)

# Make it OK to convert relative paths when adding interface sources to targets
CMAKE_POLICY (SET CMP0076 NEW)

ADD_LIBRARY (${libName} SHARED "")

SET_TARGET_PROPERTIES (${libName} PROPERTIES VERSION ${PROJECT_VERSION})
SET_TARGET_PROPERTIES (${libName} PROPERTIES SOVERSION 1)

ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(src)
