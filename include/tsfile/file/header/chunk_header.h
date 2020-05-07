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
#include <metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {

                using namespace iotdb::tsfile::file::metadata;

                /**
                 * Class that holds the responsibility to model a chunk header
                 */
                class chunk_header {

                public:
                    /**
                     * Construct a chunk header
                     * @param measurementID     id of measurement
                     * @param dataSize          size of the data
                     * @param headerSize        size of the header
                     * @param dataType          type of the data
                     * @param compressionType   type of compression
                     * @param encoding          type of encoding
                     * @param numOfPages        numeber of pages
                     */
                    chunk_header(std::string measurementID,
                                int dataSize,
                                int headerSize,
                                ts_datatype dataType,
                                compression_type compressionType,
                                ts_encoding encoding,
                                int numOfPages): _measurement_id(measurementID),
                                                 _data_size(dataSize),
                                                 _datatype(dataType),
                                                 _compression_type(compressionType),
                                                 _encoding_type(encoding),
                                                 _num_of_pages(numOfPages) {
                    }
                    friend ostream& operator<<(ostream& os, const chunk_header& dt);
                    size_t to_buffer(bytebuffer& buffer);
                    std::string get_measurement_id() const;
                    void set_measurement_id(const std::string& id) const;
                    compression_type get_compression_type() const;
                    void set_compression_type(const compression_type& type) const;
                    ts_datatype get_ts_datatype() const;
                    void set_ts_datatype(const ts_datatype& type) const;
                    ts_encoding get_ts_encoding() const;
                    void set_ts_encoding(const ts_encoding& type) const;
                    int get_num_of_pages() const;
                    void set_num_of_pages(const int& num_of_pages);
                    std::string str() const;

                private:
                    std::string _measurement_id;
                    int _data_size;
                    ts_datatype _datatype;
                    compression_type _compression_type;
                    ts_encoding _encoding_type;
                    int _num_of_pages;
                };
                ostream& operator<<(ostream& os, const chunk_header& header)
                {
                    /*
                      length += ReadWriteIOUtils.write(MetaMarker.CHUNK_HEADER, outputStream);
                      length += ReadWriteIOUtils.write(measurementID, outputStream);
                      length += ReadWriteIOUtils.write(dataSize, outputStream);
    length += ReadWriteIOUtils.write(dataType, outputStream);
    length += ReadWriteIOUtils.write(numOfPages, outputStream);
    length += ReadWriteIOUtils.write(compressionType, outputStream);
    length += ReadWriteIOUtils.write(encodingType, outputStream);
                     * */
                    return os;
                }
                /**
                 *
                 * @tparam T
                 * @param stream
                 * @param marker_read
                 * @return
                 */
                template<typename T>
                std::unique_ptr <chunk_header> make_chunk_header(const T &stream, bool marker_read) {
                    if (!marker_read) {
                        char marker;
                        stream.get(&marker)
                        if (marker != iotdb::tsfile::file::CHUNK_HEADER) {
                            throw std::runtime_error("Invalid header");
                        }
                    }
                }
            }
        }
    }
}
#endif //IOTDB_NATIVE_CHUNK_HEADER_H
