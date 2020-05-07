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
if(WIN32)
    # we support just windows 10
    set(LINK_DEPENDENCIES ${Boost_LIBRARIES} catch_lib)
    add_definitions(-D_WIN32_WINNT=0x0A00)
else()
    add_definitions(-Wall -Wextra -pedantic)
    #add_definitions(-fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
    set(LINK_DEPENDENCIES pthread catch_lib) #  asan ubsan
endif()
set(IOTDB_SOURCES
    ${MAINFOLDER}/src/util/bytebuffer.cpp)
add_library(iotdb ${IOTDB_SOURCES})
set(LINK_DEPENDENCIES ${LINK_DEPENDENCIES} iotdb)
add_library(catch_lib ${MAINFOLDER}/test/tests-main.cpp)

add_executable(test01-bytebuffer util/01-bytebuffer.cpp)
target_link_libraries(test01-bytebuffer ${LINK_DEPENDENCIES})
add_test("Should_Init_ByteBuffer" test01-bytebuffer)

add_executable(test02-rwio util/02-rwio.cpp)
target_link_libraries(test02-rwio ${LINK_DEPENDENCIES})
add_test("Should_Read" test02-rwio)

include(CTest)