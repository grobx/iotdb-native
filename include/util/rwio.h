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

namespace iotdb {
    template<typename InputStream>
    struct is_buffer_stream {
        constexpr static bool value = InputStream::is_buffer_stream;
    };

    namespace serializer {
        constexpr std::size_t SHORT_LEN = 2;
        constexpr std::size_t INT_LEN = 4;
        constexpr std::size_t LONG_LEN = 8;
        constexpr std::size_t DOUBLE_LEN = 8;
        constexpr std::size_t FLOAT_LEN = 4;

        template<typename InputStream>
        typename std::enable_if<iotdb::is_buffer_stream<InputStream>::value, int64_t>::type
        read_int(InputStream *bstream) noexcept(false) {
            std::tuple<iotdb::vbytes, std::size_t> res = bstream->readn(INT_LEN);
            iotdb::vbytes bytes = std::get<0>(res);
            std::size_t size = std::get<1>(res);
            if (size != INT_LEN) {
                throw new std::exception();
            }
            return bconv::to_int(bytes);
        }
    }
}
