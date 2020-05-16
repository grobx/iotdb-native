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
#include <tsfile/file/footer/chunk_group_footer.h>
#include <util/rwio.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            explicit chunk_group_footer::chunk_group_footer(const std::string &device_id, long data_size, int number_of_chunks)
                    : _device_id(device_id),
                      _data_size(data_size), _number_of_chunks(number_of_chunks) {
            }
            std::string chunk_group_footer::get_device_id() const {
                return _device_id;
            }
            int chunk_group_footer::get_data_size() const {
                return _data_size;
            }

            int chunk_group_footer::get_number_of_chunks() const {
                return  _number_of_chunks;
            }
            /**
             *  Serialize the chunk data to a buffer
             * @param buffer buffer contains the bytes
             * @return the dimension of the buffer.
             */
            size_t chunk_group_footer::to_buffer(iotdb::util::bytebuffer &buffer) const {
                size_t length = 0;
                /*
                length+=util::rwio::write<int8_t>(iotdb::tsfile::file::CHUNK_GROUP_FOOTER, buffer);
                length+=util::rwio::write<std::string>(_device_id, buffer);
                length+=util::rwio::write<int>(_data_size, buffer);
                length+=util::rwio::write<int>(_number_of_chunks, buffer);
                 */
                return length;
            }
        }
    }
}