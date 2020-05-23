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
#ifndef IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H
#define IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H

#include <string>
#include <unordered_map>

#include <tsfile/file/metadata/device_metadata_index.h>
#include <tsfile/utils/bloom_filter.h>
#include <util/bitset.h>
#include <util/bytebuffer.h>
#include <util/rwio.h>
#include <write/schema/measurement_schema.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb {
    namespace tsfile {
        namespace file {
            class file_metadata {
                std::unordered_map<std::string, metadata::device_metadata_index> _device_map;
                std::unordered_map<std::string, metadata::measurement_schema> _measurement_map;
                std::string _created_by;
                int32_t _total_chunk_num;
                int32_t _invalid_chunk_num;
                std::unique_ptr<utils::bloom_filter> _bloom_filter;

            public:
                explicit file_metadata(util::buffer_window& buf) {
                    int32_t size;

                    size = rwio::read<int32_t>(buf).value();
                    if (size > 0) {
                        for (int i = 0; i < size; ++i) {
                            std::string key = rwio::read<std::string>(buf).value_or("");
                            metadata::device_metadata_index value(buf);
                            _device_map.insert({key, value});
                        }
                    }

                    size = rwio::read<int32_t>(buf).value();
                    if (size > 0) {
                        for (int i = 0; i < size; ++i) {
                            std::string key = rwio::read<std::string>(buf).value_or("");
                            metadata::measurement_schema value(buf);
                            _measurement_map.insert({key, value});
                        }
                    }

                    if (rwio::read<bool>(buf) == true) {
                        _created_by = rwio::read<std::string>(buf).value_or("");
                    }

                    _total_chunk_num = rwio::read<int32_t>(buf).value();
                    _invalid_chunk_num = rwio::read<int32_t>(buf).value();

                    // read bloom filter
                    if (buf.size() > 0) {
                        util::buffer_window bytes = rwio::read<util::buffer_window>(buf).value();
                        int32_t filter_size = rwio::read<int32_t>(buf).value();
                        int32_t hash_function_size = rwio::read<int32_t>(buf).value();
                        _bloom_filter = std::make_unique<utils::bloom_filter>(bytes, filter_size, hash_function_size);
                    }
                }
            };
        }
    }
}

#endif // IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H
