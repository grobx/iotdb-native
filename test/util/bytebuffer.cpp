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

#include "../catch.hpp"
#include <util/bytebuffer.h>
using namespace iotdb::util;

SCENARIO( "bytebuffer should be initialized correctly", "[bytebuffer]" ) {
    GIVEN("a bytebuffer with predefined values") {
        bytebuffer buffer{1,25,32};
        WHEN( "we access to values by index" ) {
            auto pos1 = buffer[0];
            auto pos2 = buffer[1];
            auto pos3 = buffer[2];
            THEN( "the correct values are accessed correctly" ) {
                REQUIRE( 1 == pos1 );
                REQUIRE( 25 == pos2 );
                REQUIRE( 32 == pos3);
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
        THEN(" i can read all the data") {
            for(int i = 0; i < 3; i++) {
                buffer[i] = i;
            }
            std::vector<char> data = buffer.read_all();
            REQUIRE( 0 == data[0]);
            REQUIRE( 1 == data[1]);
            REQUIRE( 2 == data[2]);
        }
        THEN("i can read at most n bytes") {
            for(int i = 0; i < 3; i++) {
                buffer[i] = i * 2;
            }
            auto data = buffer.read_n(2);
            REQUIRE( 0 == data.value()[0]);
            REQUIRE( 2 == data.value()[1]);
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

