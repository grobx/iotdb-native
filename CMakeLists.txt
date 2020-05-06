cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
file(STRINGS "VERSION" VERSION_STRING)
project(IOTDB VERSION "${VERSION_STRING}" LANGUAGES CPP)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
##################################################
# Helper Macros
##################################################
macro(log var)
    message(STATUS "${var}: ${${var}}")
endmacro()

macro(set_if_unset var val)
    if(NOT ${var})
        set(${var} "${val}")
    endif()
    log(${var})
endmacro()
##################################################
# Includes
##################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeDependentOption)
include(CTest)

##################################################
# Internal settings
##################################################
log(PROJECT_VERSION)
log(CMAKE_GENERATOR)

add_definitions(-DCMAKE)

set(IOTDB_VERSION       ${PROJECT_VERSION})
set(IOTDB_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(IOTDB_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(IOTDB_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(IOTDB_SOVERSION ${IOTDB_VERSION_MAJOR})

if(CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
            OUTPUT_VARIABLE GCC_VERSION)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -static-libgcc -Wall -Wextra -Wno-strict-prototypes -Wunused-value -Wcast-align -Wunused-variable -Wundef -Wformat-security")

    if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")
        set(CMAKE_C_FLAGS_ASAN    "-O0 -g3 -fsanitize=address")
    else (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
        message(STATUS "GCC 4.8 required to run address sanitizer - please upgrade your installation")
    endif(GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)

    set(CMAKE_C_FLAGS_RELEASE     "-O2")
    set(CMAKE_C_FLAGS_DEBUG       "-O0 -g3")
    set(CMAKE_C_FLAGS_COVERAGE    "-O0 -g3 --coverage")
    set(CMAKE_C_FLAGS_CHECK       "-O2 -Werror")
    set(CMAKE_C_FLAGS_CHECKFULL   "${CMAKE_C_FLAGS_CHECK} -Wcast-qual")
endif(CMAKE_COMPILER_IS_GNUCC)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "--coverage")
endif(CMAKE_BUILD_TYPE STREQUAL "Coverage")

##################################################
# Options
##################################################
### Build Type ###
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose type of build." FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "Coverage" "ASan" "Check" "CheckFull")
log(CMAKE_BUILD_TYPE)

### Configurations ###
set_if_unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set_if_unset(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set_if_unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
log(CMAKE_INSTALL_PREFIX)
file(GLOB_RECURSE IOTDB_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_library(IOTDB STATIC ${IOTDB_SRC})
