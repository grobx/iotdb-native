/* Licensed to the Apache Software Foundation (ASF) under one
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
#include <iostream>
#include <util/bytebuffer.h>
#include <tsfile/file/header/page_header.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            page_header::page_header(int uncompressed_size,
                                     int compressed_size,
                                     const iotdb::tsfile::file::statistics &stat,
                                     bool modified) : _uncompressed_size(uncompressed_size),
                                                      _compressed_size(compressed_size),
                                                      _statistics(stat),
                                                      _modified(modified) {


            }

            void page_header::set_uncompressed_size(int uncompressed) noexcept {
                _uncompressed_size = uncompressed;
            }

            int page_header::get_uncompressed_size() const noexcept {
                return _uncompressed_size;
            }

            iotdb::tsfile::file::statistics page_header::get_statistics() const noexcept {
                return _statistics;
            }

            void page_header::set_statistics(const iotdb::tsfile::file::statistics &statistics) {
                _statistics = statistics;
            }

            bool page_header::is_modified() const noexcept {
                return _modified;
            }

            void page_header::set_modified(bool modified) noexcept {
                _modified = modified;
            }

            /**
             * Serialize an chunk header to a buffer
             * @param buffer
             * @return
             */
            size_t page_header::to_buffer(iotdb::util::bytebuffer &buffer) const {
                return 0;
            }

            /**
             * Convert the header to the corresponding string
             * @return convert string representation of the header
             */
            std::string page_header::str() const {
                std::ostringstream out;
                out << "PageHeader{uncompressedSize=";
                out << _uncompressed_size;
                out << ", compressedSize=";
                out << _compressed_size;
                out << ", statistics=";
                out << _statistics;
                out << "}";
                return out.str();
            }
        };
    }
}