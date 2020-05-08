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
#ifndef IOTDB_NATIVE_RWIO_H
#define IOTDB_NATIVE_RWIO_H

#include <optional>

#include "util/bconv.h"
#include <string>

namespace iotdb {
    namespace rwio {
        constexpr std::size_t BOOL_LEN = 1;
        constexpr std::size_t SHORT_LEN = 2;
        constexpr std::size_t INT_LEN = 4;
        constexpr std::size_t LONG_LEN = 8;
        constexpr std::size_t DOUBLE_LEN = 8;
        constexpr std::size_t FLOAT_LEN = 4;

        /**( READ BASE TYPES )**/

        template<typename InputStream>
        std::optional<bool>
        read_bool(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(BOOL_LEN);
            if (!res) {
                return {};
            }
            return res.value()[0] == 1u;
        }

        template<typename InputStream>
        std::optional<int16_t>
        read_short(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(SHORT_LEN);
            if (!res) {
                return {};
            }
            return bconv::to_short(res.value());
        }

        template<typename InputStream>
        std::optional<int32_t>
        read_int(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(INT_LEN);
            if (!res) {
                return {};
            }
            return bconv::to_int(res.value());
        }

        template<typename InputStream>
        std::optional<int64_t>
        read_long(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(LONG_LEN);
            if (!res) {
                return {};
            }
            return bconv::to_long(res.value(), LONG_LEN);
        }

        template<typename InputStream>
        std::optional<float_t>
        read_float(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(FLOAT_LEN);
            if (!res) {
                return {};
            }
            return bconv::to_float(res.value());
        }

        template<typename InputStream>
        std::optional<double_t>
        read_double(InputStream *bstream) {
            std::optional<iotdb::vbytes> res = bstream->read_n(DOUBLE_LEN);
            if (!res) {
                return {};
            }
            return bconv::to_double(res.value());
        }

        template<typename InputStream>
        std::optional<std::string>
        read_string(InputStream *bstream) {
            std::optional<int32_t> len = read_int(bstream);
            std::optional<iotdb::vbytes> res = bstream->read_n(len.value_or(-1));
            if (!res) {
                return {};
            }
            return bconv::to_string(res.value());
        }

        /**( READ ENUMS )**/

        /**( READ CONTAINERS )**/
    }
}

#endif // IOTDB_NATIVE_RWIO_H
