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

#include <cmath>
#include <iostream>

#include "../catch.hpp"
#include "util/rwio.h"
#include "util/bytebuffer.h"

#define THEN_NO_VALUE_IN(expr) THEN( "no value will be returned" ) { REQUIRE( !expr.has_value() ); }

using namespace iotdb;

SCENARIO( "rwio can read bool", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {1}" ) {
        iotdb::util::bytebuffer bstream({1});

        WHEN( "we read a bool from buffer stream" ) {
            std::optional<bool> x = rwio::read_bool(&bstream);

            THEN( "the bool true is returned" ) {
                REQUIRE( true == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no content" ) {
        iotdb::util::bytebuffer bstream({});

        WHEN( "we read a bool from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_bool(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read short", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {2,1}" ) {
        iotdb::util::bytebuffer bstream({2,1});

        WHEN( "we read a short from buffer stream" ) {
            std::optional<int16_t> x = rwio::read_short(&bstream);

            THEN( "the number 0x201 is returned" ) {
                REQUIRE( 0x201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({1});

        WHEN( "we read a short from buffer stream" ) {
            std::optional<int16_t> x = rwio::read_short(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read integer", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {4,3,2,1}" ) {
        iotdb::util::bytebuffer bstream({4,3,2,1});

        WHEN( "we read an integer from buffer stream" ) {
            std::optional<int32_t> x = rwio::read_int(&bstream);

            THEN( "the number 0x4030201 is returned" ) {
                REQUIRE( 0x4030201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read an integer from buffer stream" ) {
            std::optional<int32_t> x = rwio::read_int(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read long", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {8,7,6,5,4,3,2,1}" ) {
        iotdb::util::bytebuffer bstream({8,7,6,5,4,3,2,1});

        WHEN( "we read a long from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_long(&bstream);

            THEN( "the number 0x807060504030201 is returned" ) {
                REQUIRE( 0x807060504030201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({7,6,5,4,3,2,1});

        WHEN( "we read a long from buffer stream" ) {
            std::optional<int64_t> x = rwio::read_long(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read float", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {64,73,15,219}" ) {
        iotdb::util::bytebuffer bstream({64, 73, 15, 219});

        WHEN( "we read a float from buffer stream" ) {
            std::optional<float_t> x = rwio::read_float(&bstream);

            THEN( "the number Pi is returned" ) {
                REQUIRE( Approx( M_PI ) == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({0});

        WHEN( "we read a float from buffer stream" ) {
            std::optional<float_t> x = rwio::read_float(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read double", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {64,9,33,251,84,68,45,24}" ) {
        iotdb::util::bytebuffer bstream({64, 9, 33, 251, 84, 68, 45, 24});

        WHEN( "we read a double from buffer stream" ) {
            std::optional<double_t> x = rwio::read_double(&bstream);

            THEN( "the number Pi is returned" ) {
                REQUIRE( Approx( M_PI ) == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({0});

        WHEN( "we read a float from buffer stream" ) {
            std::optional<double_t> x = rwio::read_double(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read string", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {0,0,0,5,'i','o','t','d','b'}" ) {
        iotdb::util::bytebuffer bstream({0,0,0,5,'i','o','t','d','b'});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN( "the string 'iotdb' is returned" ) {
                REQUIRE( std::string("iotdb") == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content (1)" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }

    GIVEN( "a buffer stream with no enough content (2)" ) {
        iotdb::util::bytebuffer bstream({0,0,0,2,'x'});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read_string(&bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}
