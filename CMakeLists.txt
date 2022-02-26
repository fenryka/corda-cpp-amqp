# Want to be able to use the new method of setting the project version
CMAKE_POLICY (SET CMP0048 NEW)

CMAKE_MINIMUM_REQUIRED (VERSION 3.10)

PROJECT (CORDA-AMQP-CPP VERSION 0.0.3)

ADD_DEFINITIONS ("-Wall -g -ansi -pedantic")

#
# Enable for help debugging the code, will cause verbose output from
# the code to be enabled
#
# ADD_DEFINITIONS ("-DSRC_DEBUG")

#
# Set this to true to help debug any issues with cmake
#
set (CMAKE_VERBOSE_MAKEFILE "FALSE" CACHE BOOL "" FORCE)

#
# For "reasons" something to do with the way the command line compiler
# is invoked on MacOS /usr/local/include is removed from the 
# system include path so add it back in or we will fail to find
# qpid-python files as brew installs it there
#
if(APPLE)
    include_directories (/usr/local/include)
    link_directories (/usr/local/lib)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    MESSAGE(CLANG Compiler used)
    add_compile_definitions(COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(COMPILER_GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-attributes")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# Give every lib access to each lib
#
INCLUDE_DIRECTORIES(libs)

ADD_SUBDIRECTORY (libs)
ADD_SUBDIRECTORY (bin)
