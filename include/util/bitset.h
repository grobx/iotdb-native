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
#ifndef IOTDB__UTIL__BITSET__H
#define IOTDB__UTIL__BITSET__H

#include <bitset>

#include <iotdb.h>
#include <util/bytebuffer.h>
#include <util/rwio.h>

namespace iotdb { namespace util {

class bitset : public std::vector<bool> {

public:
    template<size_t Size>
    static void inline push_bitset(std::vector<bool>& v, std::bitset<Size>& x) {
        size_t size = v.size();
        size_t new_size = size + Size;
        v.resize(new_size);
        for (size_t i = 0; i < Size; ++i) {
            v[size+i] = x[i];
        }
    }

    bitset(util::bytebuffer&& buf) {
        // TODO? buf = buf.slice()
        buf.set_order(tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN);
        int n;
        auto found = std::find_if(buf.rbegin(), buf.rend(), [](const auto c) {
            return c != 0;
        });
        if (found != buf.rend()) {
            n = std::distance(found, buf.rend()); // -1;
        } else {
            n = 0;
        }
        buf.limit(n);
//        reserve(((n + 7) / 8) * 64);
        std::bitset<64> data;
        while (buf.remaining() >= 8) {
            data = rwio::read<int64_t>(buf).value();
            push_bitset(*this, data);
        }
        data = 0;
        for (int remaining = buf.remaining(), i=0; i<remaining; ++i) {
            data |= buf.read() << (8 * i);
        }
        if (data != 0) {
            push_bitset(*this, data);
        }
    }

    bitset(container_type& bytes) : bitset(util::bytebuffer(std::move(bytes))) {}
};

}}

#endif // IOTDB__UTIL__BITSET__H
