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
#include <util/buffer_window.h>

using namespace iotdb;

SCENARIO( "buffer_window", "[bitset]" ) {
    GIVEN( "a byte buffer" ) {
        util::bytebuffer b {0,1,2,3,4,5};
        util::bytebuffer br = b;
        std::reverse(br.begin(), br.end());

        WHEN( "we construct a buffer window in big endian (default)" ) {
            util::buffer_window w {b.begin(), b.end()};

            THEN( "they have the same size" ) {
                REQUIRE( w.size() == b.size() );
            }

            THEN( "we can access the first element" ) {
                REQUIRE( w[0] == b[0] );
            }

            THEN( "they have the same elements" ) {
                for (size_t i = 0; i < b.size(); ++i) {
                    INFO( "for i=" << i );
                    REQUIRE( w[i] == b[i] );
                }
            }

            THEN( "we can iterate through elements" ) {
                size_t i = 0;
                for (auto it = w.begin(); it != w.end(); ++it) {
                    REQUIRE( *it == b[i] );
                    ++i;
                }
            }

            THEN( "we can iterate through elements in reverse order" ) {
                size_t i = 0;
                for (auto it = w.rbegin(); it != w.rend(); ++it) {
                    REQUIRE( *it == br[i] );
                    ++i;
                }
            }
        }

        WHEN( "we construct a buffer window in little endian" ) {
            tsfile::encoding::endian_type endianess =
                    tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN;
            util::buffer_window w {b.begin(), b.end(), endianess};

            THEN( "they have the same size" ) {
                REQUIRE( w.size() == b.size() );
            }

            THEN( "we can access the first element" ) {
                REQUIRE( w[0] == b[0] );
            }

            THEN( "they have the same elements, but in reverse order" ) {
                for (size_t i = 0; i < b.size(); ++i) {
                    INFO( "for i=" << i );
                    REQUIRE( w[i] == b[i] );
                }
            }

            THEN( "we can iterate through elements" ) {
                size_t i = 0;
                for (auto it = w.begin(); it != w.end(); ++it) {
                    REQUIRE( *it == b[i] );
                    ++i;
                }
            }

            THEN( "we can iterate through elements in reverse order" ) {
                size_t i = 0;
                for (auto it = w.rbegin(); it != w.rend(); ++it) {
                    REQUIRE( *it == br[i] );
                    ++i;
                }
            }
        }
    }
}
