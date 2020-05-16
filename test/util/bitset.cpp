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

#include "util/bitset.h"

using namespace iotdb;

SCENARIO( "bitset", "[bitset]" ) {
    GIVEN( "a sequence bytes" ) {
        util::bytebuffer bytes
                ({0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01});

        WHEN( "we create a bitset out of it" ) {
            util::bitset bits(std::move(bytes));

            THEN ( "there are 64 bits") {
                REQUIRE( bits.size() == 64 );

                std::bitset<64> x = 0x0101010101010101;
                std::basic_string<int> rs = x.to_string(0, 1);

                AND_THEN ( "we get " << x.to_string() ) {
                    for (int i = 0; i < 64; ++i) {
                        INFO( "for i=" << i );
                        REQUIRE( rs[i] == bits[i] );
                    }
                }
            }
        }
    }
}
