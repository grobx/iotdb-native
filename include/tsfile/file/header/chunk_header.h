/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef IOTDB_NATIVE_CHUNK_HEADER_H
#define IOTDB_NATIVE_CHUNK_HEADER_H
#include <iostream>
#include <concept>

namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {
                const int8_t CHUNK_MARKER =
                std::unique_ptr<chunk_header> make_chunk_header(const istream& stream, bool marker_read) {
                    if (!marker_read) {
                        char marker;
                        stream.get(&marker)
                    }
                }
                std::unique_ptr<chunk_header> make_chunk_header(const iotdb::util::bytebuffer& buffer) {
                }
                std::unique_ptr<chunk_header> make_chunk_header(const uint8_t* data, size_t n) {
                }
                class chunk_header {
                };
            }

        }
    }
}


#endif //IOTDB_NATIVE_CHUNK_HEADER_H
