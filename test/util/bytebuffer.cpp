/**
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#include <catch2/catch.hpp>

#include <util/bytebuffer.h>

using namespace iotdb::util;

SCENARIO( "bytebuffer should be initialized correctly", "[bytebuffer]" ) {
    GIVEN("a bytebuffer with predefined values") {
        bytebuffer buffer{1,25,32};
        WHEN( "we access to values by index" ) {
            THEN( "the correct values are accessed correctly" ) {
                REQUIRE( 1 == buffer[0] );
                REQUIRE( 25 == buffer[1] );
                REQUIRE( 32 == buffer[2]);
            }
        }
    }
}
SCENARIO(" Assuring capacity of the buffer", "[bytebuffer]") {
      GIVEN("a bytebuffer with predefined size ") {
          bytebuffer buffer(10);
          WHEN("we ask to ensure the size") {
              THEN(" we double the capacity") {
                  size_t capacity = buffer.capacity();
                  buffer.ensure_space();
                  REQUIRE(capacity *2 == buffer.capacity());
              }
          }
      }
}
SCENARIO( "Iterating a bytebuffer should work", "[bytebuffer]") {
    bytebuffer buffer {1, 2, 3, 4, 7, 8};
    WHEN ("we loop through the byte buffer") {
        THEN(" the iteration is performed correctly") {
            int8_t sum = 0;
            const int8_t matched = 25;
            for (auto data : buffer) {
                sum+=data;
            }
            REQUIRE( matched == sum);
        }
    }
}
SCENARIO("We should be able to write and read correctly in a byte buffer") {
    bytebuffer buffer(10);
    WHEN(" assign bytes to the byte buffer") {
        THEN("then bytes are in the correct position in the array") {
            for(int i = 0; i < 3; i++) {
                buffer[i] = i;
            }
            REQUIRE( 0 == buffer[0]);
            REQUIRE( 1 == buffer[1]);
            REQUIRE( 2 == buffer[2]);
        }
        THEN("i can use the iterators" ) {
            for(int i = 0; i < 3; i++) {
                buffer[i] = i * 2;
            }
            auto j = 0;
            for(char v: buffer) {
                if (j == 0 ){
                    REQUIRE( 0 == v);
                }
                if (j == 1) {
                    REQUIRE( 2 == v);
                }
                if (j == 2) {
                    REQUIRE( 4 == v);
                }
                j++;
            }
        }
    }

}

