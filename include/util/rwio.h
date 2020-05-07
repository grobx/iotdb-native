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
#include "util/bconv.h"
#include <std::string>

namespace iotdb {
    namespace serializer {
        constexpr std::size_t SHORT_LEN = 2;
        constexpr std::size_t INT_LEN = 4;
        constexpr std::size_t LONG_LEN = 8;
        constexpr std::size_t DOUBLE_LEN = 8;
        constexpr std::size_t FLOAT_LEN = 4;

        template<typename InputStream>
        int64_t read_int(InputStream *bstream) noexcept(false) {
            std::optional <std::vector<uint8_t>> res = bstream->read_n(INT_LEN);
            if (!res) {
                throw new std::exception();
            }
            return bconv::to_int(res.value());
        }

        template<typename InputStream>
        int64_t read_int(InputStream &bstream) noexcept(false) {
            std::optional <std::vector<uint8_t>> res = bstream.read_n(INT_LEN);
            if (!res) {
                throw new std::exception();
            }
            return bconv::to_int(res.value());
        }

        template<typename InputStream>
        std::optional <std::string> read_string(InputStream &bstream) noexcept(false) {
            int strLength = read_int(bstream);
            auto bytes = std::make_unique<char[]>(strLength);
            int readLen = bstream.read(bytes, strLength);
            if (readLen != strLength) {
                return {};
            }
            return std::string(data);
        }
    }
}
}
