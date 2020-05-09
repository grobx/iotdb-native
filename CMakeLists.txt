#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
file(STRINGS "VERSION" VERSION_STRING)
project(iotdb-native VERSION "${VERSION_STRING}" LANGUAGES CXX)
SET (CMAKE_VERBOSE_MAKEFILE 0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeDependentOption)
include (CTest)
enable_testing()
include_directories("${MAINFOLDER}/include")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

##################################################
# Internal settings
##################################################

set(iotdb-native_version       ${PROJECT_VERSION})
set(iotdb-native_MAJOR ${PROJECT_VERSION_MAJOR})
set(iotdb-native_MINOR ${PROJECT_VERSION_MINOR})
set(iotdb-native_PATCH ${PROJECT_VERSION_PATCH})
set(iotdb-native_SOVERSION ${iotdb-native_MAJOR})
set(VCPKG_HOME $ENV{HOME}/scripts/buildsystems/vcpkg.cmake)
add_definitions(-DCMAKE -DCMAKE_TOOLCHAIN_FILE=${VCPKG_HOME})
find_package(Threads REQUIRED)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    execute_process(COMMAND
            ${CMAKE_CXX_COMPILER} -dumpversion
            OUTPUT_VARIABLE GCC_VERSION)
    string(STRIP ${GCC_VERSION} GCC_VERSION)
    MESSAGE(STATUS "gcc version: [" ${GCC_VERSION} "]")

    # this works on gentoo, but not on travis/ubuntu, let's hard-code the value
    #execute_process(COMMAND
    #    "which" "gcov-${GCC_VERSION}"
    #    OUTPUT_VARIABLE GCOV_TOOL)
    #MESSAGE(STATUS "gcov: [" ${GCOV_TOOL} "]")
    #string(STRIP ${GCOV_TOOL} GCOV_TOOL)
    #MESSAGE(STATUS "gcov(fixed): [" ${GCOV_TOOL} "]")
    set(GCOV_TOOL "gcov-5")

    add_custom_target("coverage"
            COMMAND "lcov" --directory . --zerocounters
            COMMAND ctest
            COMMAND "lcov" --directory . --capture --output-file coverage.info --gcov-tool ${GCOV_TOOL}
            COMMAND "lcov" --remove coverage.info "'/t/*'" "'/boost_1_63_0/*'" "'/usr/*'" --output-file coverage.info.cleaned
            COMMAND "rm" coverage.info

            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
    add_custom_target("coverage-report"
            COMMAND "genhtml" -o coverage coverage.info.cleaned
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS "coverage"
            )
endif()
### Configurations ###
include_directories(${MAINFOLDER}/include)
add_subdirectory(test)
