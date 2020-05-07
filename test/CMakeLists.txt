find_package(Catch2 REQUIRED)

if(WIN32)
    # we support just windows 10
    set(LINK_DEPENDENCIES ${Boost_LIBRARIES} catch_lib)
    add_definitions(-D_WIN32_WINNT=0x0A00)
else()
    add_definitions(-Wall -Wextra -pedantic)
    #add_definitions(-fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
    set(LINK_DEPENDENCIES pthread catch_lib) #  asan ubsan
endif()
set(IOTDB_SOURCES ${MAINFOLDER}/src/util/bytebuffer.cpp)
add_library(catch_lib ${MAINFOLDER}/test/tests-main.cpp)

add_executable(test01-bytebuffer 01-bytebuffer.cpp ${IOTDB_SOURCES})
set_target_properties(test01-bytebuffer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
target_link_libraries(test01-bytebuffer ${LINK_DEPENDENCIES})
add_test("Should_Init_ByteBuffer" test01-bytebuffer)

add_executable(rwio util/rwio.cpp ${IOTDB_SOURCES})
target_link_libraries(rwio Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(rwio)
