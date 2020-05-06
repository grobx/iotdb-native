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
namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {
                std::unique_ptr<chunk_header> make_chunk_header(const istream& stream, bool marker_read) {
                    if (!marker_read) {
                        char marker;
                        stream.get(&marker)
                        uint8_t m = static_cast<uint8_t>(marker);
                        if (marker != MetaMarker.CHUNK_HEADER) {
                            MetaMarker.handleUnexpectedMarker(marker);
                        }
                    }
                    String measurementID = ReadWriteIOUtils.readString(inputStream);
                    int dataSize = ReadWriteIOUtils.readInt(inputStream);
                    TSDataType dataType = TSDataType.deserialize(ReadWriteIOUtils.readShort(inputStream));
                    int numOfPages = ReadWriteIOUtils.readInt(inputStream);
                    CompressionType type = ReadWriteIOUtils.readCompressionType(inputStream);
                    TSEncoding encoding = ReadWriteIOUtils.readEncoding(inputStream);
                    return new ChunkHeader(measurementID, dataSize, dataType, type, encoding, numOfPages);
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
