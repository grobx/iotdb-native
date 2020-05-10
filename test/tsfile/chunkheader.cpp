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
#include <string>
#include <utility>
#include <util/bytebuffer.h>
#include <tsfile/file/header/chunk_header.h>

using namespace iotdb;

SCENARIO("Serializing a chunk header", "[chunkheader]") {
    GIVEN("A chunk header compresses with gzip") {
        iotdb::tsfile::file::chunk_header chunk("910920192", 1024, 80,
                                                ts_datatype::TEXT,
                                                compression_type::GZIP,
                                                ts_encoding::PLAIN_DICTIONARY, 3);
        WHEN("serialized to a buffer") {
            iotdb::util::bytebuffer buffer;
            chunk.to_buffer(buffer);
            THEN("data is serialized correctly") {
                REQUIRE(0x807060504030201 == x.value());
            }
        }
    }
    GIVEN("A chunk header compresses with gzip") {
        iotdb::tsfile::file::chunk_header chunk("910920192", 1024, 80,
                                                ts_datatype::TEXT,
                                                compression_type::GZIP,
                                                ts_encoding::PLAIN_DICTIONARY, 3);
        WHEN("serialized to a buffer") {
            iotdb::util::bytebuffer buffer;
            chunk.to_buffer(buffer);
            THEN("data is serialized correctly") {
                REQUIRE(0x807060504030201 == x.value());
            }
        }
    }
}

