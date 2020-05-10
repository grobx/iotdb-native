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
        iotdb::util::bytebuffer bstream{1};
        WHEN( "we read a bool from buffer stream" ) {
            std::optional<bool> x = rwio::read<bool>(bstream);

            THEN( "the bool true is returned" ) {
                REQUIRE( true == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no content" ) {
        iotdb::util::bytebuffer bstream({});

        WHEN( "we read a bool from buffer stream" ) {
            std::optional<int64_t> x = rwio::read<bool>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read short", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {2,1}" ) {
        iotdb::util::bytebuffer bstream({2,1});

        WHEN( "we read a short from buffer stream" ) {
            std::optional<int16_t> x = rwio::read<short>(bstream);

            THEN( "the number 0x201 is returned" ) {
                REQUIRE( 0x201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({1});

        WHEN( "we read a short from buffer stream" ) {
            std::optional<int16_t> x = rwio::read<short>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read integer", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {4,3,2,1}" ) {
        iotdb::util::bytebuffer bstream({4,3,2,1});

        WHEN( "we read an integer from buffer stream" ) {
            std::optional<int32_t> x = rwio::read<int32_t>(bstream);

            THEN( "the number 0x4030201 is returned" ) {
                REQUIRE( 0x4030201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read an integer from buffer stream" ) {
            std::optional<int32_t> x = rwio::read<int32_t>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read long", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {8,7,6,5,4,3,2,1}" ) {
        iotdb::util::bytebuffer bstream({8,7,6,5,4,3,2,1});

        WHEN( "we read a long from buffer stream" ) {
            std::optional<int64_t> x = rwio::read<int64_t>(bstream);

            THEN( "the number 0x807060504030201 is returned" ) {
                REQUIRE( 0x807060504030201 == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({7,6,5,4,3,2,1});

        WHEN( "we read a long from buffer stream" ) {
            std::optional<int64_t> x = rwio::read<int64_t>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read float", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {64,73,15,219}" ) {
        iotdb::util::bytebuffer bstream{64, 73, 15, 125};

        WHEN( "we read a float from buffer stream" ) {
            std::optional<float_t> x = rwio::read<float_t>(bstream);

            THEN( "the number Pi is returned" ) {
                REQUIRE( Approx( M_PI ) == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({0});

        WHEN( "we read a float from buffer stream" ) {
            std::optional<float_t> x = rwio::read<float_t>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read double", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {64,9,33,125,84,68,45,24}" ) {
        iotdb::util::bytebuffer bstream({64, 9, 33, -5, 84, 68, 45, 24});

        WHEN( "we read a double from buffer stream" ) {
            std::optional<double_t> x = rwio::read<double_t>(bstream);

            THEN( "the number Pi is returned" ) {
                REQUIRE( Approx( M_PI ) == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content" ) {
        iotdb::util::bytebuffer bstream({0});

        WHEN( "we read a float from buffer stream" ) {
            std::optional<double_t> x = rwio::read<double_t>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

SCENARIO( "rwio can read string", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {0,0,0,5,'i','o','t','d','b'}" ) {
        iotdb::util::bytebuffer bstream({0,0,0,5,'i','o','t','d','b'});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read<std::string>(bstream);

            THEN( "the string 'iotdb' is returned" ) {
                REQUIRE( std::string("iotdb") == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with no enough content (1)" ) {
        iotdb::util::bytebuffer bstream({3,2,1});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read<std::string>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }

    GIVEN( "a buffer stream with no enough content (2)" ) {
        iotdb::util::bytebuffer bstream({0,0,0,2,'x'});

        WHEN( "we read a string from buffer stream" ) {
            std::optional<std::string> x = rwio::read<std::string>(bstream);

            THEN_NO_VALUE_IN(x);
        }
    }
}

using namespace iotdb::tsfile::file::metadata;
SCENARIO( "rwio can read enums", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {0,2}" ) {
        iotdb::util::bytebuffer bstream({0,2});

        WHEN( "we read a compression_type" ) {
            std::optional<compression_type> x =
                rwio::read_enum<compression_type>(bstream);

            THEN( "we got compression_type::GZIP" ) {
                REQUIRE( compression_type::GZIP == x.value() );
            }
        }

        WHEN( "we read a ts_datatype" ) {
            std::optional<ts_datatype> x =
                rwio::read_enum<ts_datatype>(bstream);

            THEN( "we got ts_datatype::INT64" ) {
                REQUIRE( ts_datatype::INT64 == x.value() );
            }
        }

        WHEN( "we read a ts_encoding" ) {
            std::optional<ts_encoding> x =
                rwio::read_enum<ts_encoding>(bstream);

            THEN( "we got ts_encoding::INT64" ) {
                REQUIRE( ts_encoding::RLE == x.value() );
            }
        }
    }
}

SCENARIO( "rwio can read int list", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {0,0,0,2,8,7,6,5,4,3,2,1}" ) {
        iotdb::util::bytebuffer bstream{0,0,0,2,8,7,6,5,4,3,2,1};

        WHEN( "we read an int list from buffer stream" ) {
            std::optional<std::vector<int32_t>> x =
                rwio::read_list<int32_t>(bstream);

            THEN( "the list {0x8070605,0x4030201} is returned" ) {
                REQUIRE( std::vector({0x8070605,0x4030201}) == x.value() );
            }
        }
    }

    GIVEN( "a buffer stream with content: {0,0,0,0}" ) {
        iotdb::util::bytebuffer bstream{0,0,0,0};

        WHEN( "we read an int list from buffer stream" ) {
            std::optional<std::vector<int32_t>> x =
                rwio::read_list<int32_t>(bstream);

            THEN( "the list is empty" ) {
                REQUIRE( 0 == x.value().size() );
            }
        }
    }
}

SCENARIO( "rwio can read string list", "[rwio]" ) {
    GIVEN( "a buffer stream with content: {0,0,0,2,0,0,0,3,'i','o','t',0,0,0,2,'d','b'}" ) {
        iotdb::util::bytebuffer bstream({0,0,0,2,0,0,0,3,'i','o','t',0,0,0,2,'d','b'});

        WHEN( "we read a string list from buffer stream" ) {
            std::vector<std::string> x =
                rwio::read_list<std::string>(bstream);

            THEN( "the list {'iot','db'} is returned" ) {
                REQUIRE( std::vector({std::string("iot"), std::string("db")}) == x );
            }
        }
    }

    GIVEN( "a buffer stream with content: {0,0,0,0}" ) {
        iotdb::util::bytebuffer bstream({0,0,0,0});
        WHEN( "we read a string list from buffer stream" ) {
            std::vector<std::string> x =
                rwio::read_list<std::string>(bstream);

            THEN( "the list is empty" ) {
                REQUIRE( 0 == x.size() );
            }
        }
    }
}
