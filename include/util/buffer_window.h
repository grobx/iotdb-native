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
#ifndef IOTDB__UTIL__BUFFER_WINDOW
#define IOTDB__UTIL__BUFFER_WINDOW

#include <iterator>

#include <iotdb.h>
#include <tsfile/encoding/endian_type.h>
#include <util/bytebuffer.h>
#include <util/conv/iterator.h>

namespace iotdb { namespace util {

template <typename It>
class basic_buffer_window {
    It f;
    It l;
    tsfile::encoding::endian_type o;

public:
    using iterator = typename conv::basic_iterator<It>;
    using reverse_iterator = typename conv::basic_iterator<std::reverse_iterator<It>>;
    using reference = typename iterator::reference;
    using value_type = typename iterator::value_type;

    explicit basic_buffer_window(
            It first, It last,
            tsfile::encoding::endian_type order = tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN)
        : f{first}, l{last}, o{order} {}

    explicit basic_buffer_window(
            util::bytebuffer& buffer,
            tsfile::encoding::endian_type order = tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN)
        : basic_buffer_window(buffer.begin(), buffer.end(), order) {}

    iterator begin() const { return iterator(f, o); }

    iterator end() const { return iterator(l, o); }

    reverse_iterator rbegin() const { return reverse_iterator(std::reverse_iterator(l), o); }

    reverse_iterator rend() const { return reverse_iterator(std::reverse_iterator(f), o); }

    void order(tsfile::encoding::endian_type order) { o = order; }

    tsfile::encoding::endian_type order() { return o; }

    void limit(It limit) { l = limit; }

    size_t size() const { return std::distance(f, l); }

    std::optional<basic_buffer_window<It>>
    read_n(size_t len) {
        if (len <= 0 || len > size()) {
            return {};
        }
        It oldf = f;
        f += len;
        return basic_buffer_window<It>(oldf, f, o);
    }

    reference operator[](size_t idx) const {
        return *(f + idx);
    }
};

using buffer_window = basic_buffer_window<bytebuffer::iterator>;

}}

#endif // IOTDB__UTIL__BUFFER_WINDOW
