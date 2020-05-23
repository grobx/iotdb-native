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
#include <util/buffer_window.h>
#include <util/rwio.h>

namespace iotdb { namespace util {

class bitset : public std::vector<bool> {

private:
    template<size_t Size>
    void inline init(std::vector<std::bitset<Size>> words) {
        for (const std::bitset<Size>& w : words) {
            push_bitset(w);
        }
    }

public:
    bitset() {}

    explicit bitset(const std::vector<std::bitset<64>>& words) {
        init(words);
    }

    explicit bitset(const util::buffer_window& bw) {
        util::buffer_window buf = bw;
        buf.order(tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN);
        auto found = std::find_if(buf.rbegin(), buf.rend(), [](const auto c) {
            return static_cast<uint64_t>(c) != 0;
        });
        buf.limit(found.base().base());
//        reserve(((n + 7) / 8) * 64);
        std::vector<std::bitset<64>> words;
        while (buf.size() >= 8) {
            words.emplace_back(rwio::read<uint64_t>(buf).value());
        }
        std::bitset<64> data = 0;
        for (size_t i = 0; i <= buf.size(); ++i) {
            data |= rwio::read<uint8_t>(buf).value() << (8 * i);
        }
        if (data != 0) {
            words.push_back(data);
        }
        init(words);
    }

    template<size_t Size>
    void inline push_bitset(const std::bitset<Size>& x) {
        size_t sz = size();
        size_t new_size = sz + Size;
        resize(new_size);
        for (size_t i = 0; i < Size; ++i) {
            (*this)[sz+i] = x[i];
        }
    }
};

}}

#endif // IOTDB__UTIL__BITSET__H
