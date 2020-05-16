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

#include <util/bytebuffer.h>
#include <util/rwio.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb { namespace tsfile { namespace file {
class device_metadata_index {
public:
    device_metadata_index(util::bytebuffer& buf) {

    }
};

class measurement_schema {
public:
    measurement_schema(util::bytebuffer& buf) {

    }
};

class file_metadata {
    std::unordered_map<std::string, device_metadata_index> _device_map;
    std::unordered_map<std::string, measurement_schema> _measurement_map;
    std::string _created_by;
    int32_t _total_chunk_num;
    int32_t _invalid_chunk_num;

public:
    file_metadata(util::bytebuffer& buf) {
        int32_t size;

        size = rwio::read<int32_t>(buf).value_or(-1);
        if (size > 0) {
            for (int i = 0; i < size; ++i) {
                std::string key = rwio::read<std::string>(buf).value_or("");
                device_metadata_index value(buf);
                _device_map.insert({key, value});
            }
        }

        size = rwio::read<int32_t>(buf).value_or(-1);
        if (size > 0) {
            for (int i = 0; i < size; ++i) {
                std::string key = rwio::read<std::string>(buf).value_or("");
                measurement_schema value(buf);
                _measurement_map.insert({key,value});
            }
        }

        if (rwio::read<bool>(buf) == true) {
            _created_by = rwio::read<std::string>(buf).value_or("");
        }

        _total_chunk_num = rwio::read<int32_t>(buf).value_or(-1);
        _invalid_chunk_num = rwio::read<int32_t>(buf).value_or(-1);

        // read bloom filter
        //        if (buf.has_remaining()) {

        //        }
        //        if (buffer.hasRemaining()) {
        //            byte[] bytes = ReadWriteIOUtils.readByteBufferWithSelfDescriptionLength(buffer).array();
        //            int filterSize = ReadWriteIOUtils.readInt(buffer);
        //            int hashFunctionSize = ReadWriteIOUtils.readInt(buffer);
        //            fileMetaData.bloomFilter = BloomFilter.buildBloomFilter(bytes, filterSize, hashFunctionSize);
        //        }

        //        return fileMetaData;
    }
};

}}}

#endif // IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H
