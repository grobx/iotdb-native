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
#ifndef IOTDB__WRITE__SCHEMA__MEASUREMENT_SCHEMA__H
#define IOTDB__WRITE__SCHEMA__MEASUREMENT_SCHEMA__H

#include <string>
#include <unordered_map>

#include <tsfile/file/metadata/device_metadata_index.h>
#include <util/bytebuffer.h>
#include <util/rwio.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb { namespace tsfile { namespace file { namespace metadata {

class measurement_schema {
    std::string _measurement_id;
    ts_datatype _type;
    ts_encoding _encoding;
    compression_type _compressor;
    std::unordered_map<std::string, std::string> _props;

public:
    measurement_schema(util::bytebuffer& buf) {
        _measurement_id = rwio::read<std::string>(buf).value();
        _type = rwio::read<ts_datatype>(buf).value();
        _encoding = rwio::read<ts_encoding>(buf).value();
        _compressor = rwio::read<compression_type>(buf).value();

        int32_t size = rwio::read<int32_t>(buf).value();
        if (size > 0) {
            std::string key;
            std::string value;
            for (int i = 0; i < size; i++) {
                key = rwio::read<std::string>(buf).value();
                value = rwio::read<std::string>(buf).value();
                _props.insert({key, value});
            }
        }
    }
};

}}}}

#endif // IOTDB__WRITE__SCHEMA__MEASUREMENT_SCHEMA__H
