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

#include <iostream>

namespace iotdb { namespace util {

class bitset : public std::vector<bool> {

    void inline push_word(std::vector<bool>& v, std::bitset<64>& x) {
        for (size_t i=x.size(); i>0;) {
            v.push_back(x[--i]);
        }
    }

public:
    bitset(util::bytebuffer&& buf) {
        // TODO? buf = buf.slice()
        // FIXME buf.set_order(tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN);
        int n;
        auto found = std::find_if(buf.rbegin(), buf.rend(), [](const auto c) {return c != 0;});
        if (found != buf.rend()) {
            n = std::distance(found, buf.rend()); // -1;
        } else {
            n = 0;
        }
        buf.limit(n);
        reserve(((n + 7) / 8) * 8);
        std::bitset<64> data;
        while (buf.remaining() >= 8) {
            data = rwio::read<int64_t>(buf).value();
            push_word(*this, data);
        }
        data = 0;
        for (int remaining = buf.remaining(), j=0; j<remaining; j++) {
            data |= (buf.read() & 0xffL) << (8 * j);
        }
        if (data != 0) {
            push_word(*this, data);
        }
    }

    bitset(container_type& bytes) : bitset(util::bytebuffer(std::move(bytes))) {}
};

}}

#endif // IOTDB__UTIL__BITSET__H
