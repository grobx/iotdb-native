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
    bytebuffer buffer {1, 2};

}

