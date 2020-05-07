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

#include <iostream>

#include "catch.hpp"
#include "util/rwio.h"
#include "util/bytebuffer.h"

#define THEN_NO_VALUE_IN(expr) THEN( "no value will be returned" ) { REQUIRE( !expr.has_value() ); }

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

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read the integer from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_int(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read string", "[rwio]" ) {
    GIVEN( "a buffer stream with string contents" ) {
        iotdb::util::bytebuffer bstream({0,0,0,5,'i','o','t','d','b'});

        WHEN( "we read the string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN( "the string 'hello iotdb' is returned" ) {
                REQUIRE( std::string("iotdb") == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content (1)" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read the string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }

    GIVEN( "a buffer stream with no enough content (2)" ) {
        iotdb::util::bytebuffer bstream({0,0,0,2,'x'});

        WHEN( "we read the string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}
