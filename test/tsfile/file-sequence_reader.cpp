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

#include <tsfile/read/sequence_reader.h>

SCENARIO( "create sequence_reader instance", "[sequence_reader]" ) {
    GIVEN( "a path of a tsfile" ) {
        std::filesystem::path path =
            std::filesystem::current_path().append("TsFileSequenceReaderTest.tsfile");

        WHEN( "we create a sequence_reader" ) {
            iotdb::tsfile::read::sequence_reader r(path);

            THEN( "we can read the version number" ) {
                REQUIRE( std::string("000001") == r.read_version_number() );

                AND_THEN( "we can read the tail magic" ) {
                    REQUIRE( std::string("TsFile") == r.read_tail_magic() );

                    AND_THEN( "the metadata size and pos was read" ) {
                        REQUIRE( 0x801b == r.metadata_pos() );
                        REQUIRE( 0x11b == r.metadata_size() );
                    }
                }
            }
        }
    }

    GIVEN( "a sequence_reader of a given tsfile" ) {
        std::filesystem::path path =
            std::filesystem::current_path().append("TsFileSequenceReaderTest.tsfile");
        iotdb::tsfile::read::sequence_reader r(path);

        WHEN( "we ask if the file is complete" ) {
            bool x = r.is_complete();

            THEN ( "the file is complete" ) {
                REQUIRE( true == x );
            }
        }
    }
}
