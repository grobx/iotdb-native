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

#include <chunk_header.h>
#include <iostream>
#include <metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {

                using namespace iotdb::tsfile::file::metadata;

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
                chunk_header::chunk_header(std::string measurementID,
                                           int dataSize,
                                           int headerSize,
                                           ts_datatype dataType,
                                           compression_type compressionType,
                                           ts_encoding encoding,
                                           int numOfPages) : _measurement_id(measurementID),
                                                             _data_size(dataSize),
                                                             _datatype(dataType),
                                                             _compression_type(compressionType),
                                                             _encoding_type(encoding),
                                                             _num_of_pages(numOfPages) {
                }

                /**
                 *  Serialize the chunk data to a buffer
                 * @param buffer buffer contains the bytes
                 * @return the dimension of the buffer.
                 */
                size_t chunk_header::to_buffer(iotdb::util::bytebuffer &buffer) {
                    size_t length = 0;
                    length += ReadWriteIOUtils.write(MetaMarker.CHUNK_HEADER, outputStream);
                    length += ReadWriteIOUtils.write(measurementID, outputStream);
                    length += ReadWriteIOUtils.write(dataSize, outputStream);
                    length += ReadWriteIOUtils.write(dataType, outputStream);
                    length += ReadWriteIOUtils.write(numOfPages, outputStream);
                    length += ReadWriteIOUtils.write(compressionType, outputStream);
                    length += ReadWriteIOUtils.write(encodingType, outputStream);
                    return size_t;
                }

                /**
                 * Get the measurement id
                 * @return  identifier fo the measurement
                 */
                std::string chunk_header::get_measurement_id() const {
                    return _measurement_id;
                }

                /**
                 * Set measurement id.
                 * @param id identifier of measurement
                 */
                void chunk_header::set_measurement_id(const std::string &id) const {
                    _measurement_id = id;
                }

                /**
                 * Get the compression type
                 * @return Type of the compression.
                 */
                compression_type chunk_header::get_compression_type() const {
                    return _compression_type;
                }

                /**
                 * Set the type of the compression
                 * @param type type of the compression
                 */
                void chunk_header::set_compression_type(const compression_type &type) const {
                    _compression_type = type;
                }

                /**
                 * Get the time series type
                 * @return a time serie type.
                 */
                ts_datatype chunk_header::get_ts_datatype() const {
                    return _datatype;
                }

                /**
                 * Ser the timeseries datatype
                 * @param type datatype
                 */
                void chunk_header::set_ts_datatype(const ts_datatype &type) const {
                    _datatype = type;
                }

                /**
                 * Return the encoding of time serie encoding
                 * @return time serie encoding
                 */
                ts_encoding chunk_header::get_ts_encoding() const {
                    return _encoding_type;
                }

                /**
                 * Set the time series encoding
                 * @param type encoding of the time serie
                 */
                void chunk_header::set_ts_encoding(const ts_encoding &type) const {
                    _encoding_type = type;
                }

                /**
                 * Get the number of pages
                 * @return number of pages
                 */
                int chunk_header::get_num_of_pages() const {
                    return _number_of_pages;
                }

                /**
                 * Set the number of pages
                 * @param num_of_pages number of pages.
                 */
                void chunk_header::set_num_of_pages(const int &num_of_pages) {
                    _number_of_pages = num_of_pages;
                }
                /**
                 * Return a hexadecimal representation of the chunkheader
                 * @return
                 */
                std::string chunk_header::str() const {

                }
            }
        }
    }
}
