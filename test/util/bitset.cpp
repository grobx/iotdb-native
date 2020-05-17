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
//#include "java_executor.h"

using namespace iotdb;

SCENARIO( "push_bitset", "[bitset]" ) {
    GIVEN( "some bits in a bitset<64>" ) {
        std::string content =
                "00010000" "00010000" "00010000" "00010000"
                "00010001" "00010010" "00010011" "00010111";
        std::bitset<64> expected(content);
        constexpr size_t size = expected.size();

        WHEN( "you push this bitset<64> to a vector<bool>" ) {
            std::vector<bool> bits;
            iotdb::util::bitset::push_bitset(bits, expected);

            THEN ( "you got the right size" ) {
                REQUIRE( bits.size() == size );

                AND_THEN ( "you got the right content" ) {
                    for (size_t i = 0; i < size; ++i) {
                        INFO( "for i=" << i );
                        REQUIRE( expected[i] == bits[i] );
                    }
                }
            }
        }
    }
}

SCENARIO( "bitset", "[bitset]" ) {
    std::initializer_list<iotdb::value_type> contents
            = {0x10,0x10,0x10,0x10,0x11,0x12,0x13,0x17,
               0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
               0x00,0x00,0x00,0x00};
    constexpr size_t size = 2 * 64;

    GIVEN( "these sequence of bytes" ) {
        util::bytebuffer bytes(contents);

        WHEN( "we create a bitset out of it" ) {
            util::bitset bits(std::move(bytes));

            THEN ( "there are "<<size<<" bits") {
                REQUIRE( bits.size() == size );
                std::bitset<size> x(
                            "11101000" "11001000" "01001000" "10001000"
                            "00001000" "00001000" "00001000" "00001000"
                            "00000000" "00000000" "00000000" "00000000"
                            "00000000" "00000000" "00001000" "00001000"
                            );
                std::basic_string<int> rs = x.to_string(0, 1);

                AND_THEN ( "we get " << x.to_string() ) {
                    for (size_t i = 0; i < size; ++i) {
                        INFO( "for i=" << i );
                        REQUIRE( rs[i] == bits[i] );
                    }
                }
            }
        }
    }
}
