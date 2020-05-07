find_package(Catch2 REQUIRED)

add_executable(rwio util/rwio.cpp)
target_link_libraries(rwio Catch2::Catch2 IOTDB)

include(CTest)
include(Catch)
catch_discover_tests(rwio)
