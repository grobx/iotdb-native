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

#include "catch.hpp"
#include "util/rwio.h"
#include "util/bytebuffer.h"

using namespace iotdb;

SCENARIO( "rwio can read integer", "[rwio]" ) {
    GIVEN( "a buffer stream with {4,3,2,1} contents" ) {
        iotdb::util::bytebuffer bstream({4,3,2,1});

        WHEN( "we read the integer from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_int(&bstream);

            THEN( "the number 0x4030201 is returned" ) {
                REQUIRE( 0x4030201 == x.value() );
            }
        }
    }
}

SCENARIO( "rwio will throw an exception if buffer is not enough", "[rwio]" ) {
    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read the integer from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_int(&bstream);

            THEN( "no integer will be returned" ) {
                REQUIRE( !x.has_value() );
            }
        }
    }
}
