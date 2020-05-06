#include <catch2/catch.hpp>
#include "../include/bytebuffer.h"
#include <tuple>
SCENARIO( "bytebuffer can be read and written", "[bytebuffer]" ) {
GIVEN( "A bytebuffer initialized" ) {
iotdb::util::bytebuffer buffer{1, 255, 32, 16, 8, 32, 24, 16};
REQUIRE( buffer.size() == 7 );
WHEN( "we read 4 bytes" ) {
auto data = v.read_n(4);
THEN( "the values are read correctly" ) {
auto value = std::get<0>(data);
auto value_size = std::get<1>(data);
REQUIRE(value_size == 4)
REQUIRE(value[0] == 1)
REQUIRE(value[1] == 255)
REQUIRE(value[2] == 32)
REQUIRE(value[3] == 16)
}
}
}
}