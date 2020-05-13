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
#ifndef IOTDB__RWIO__H
#define IOTDB__RWIO__H

#include <optional>
#include <string>

#include <tsfile/file/metadata/metadata.h>
#include <util/bytebuffer.h>
#include <util/bconv.h>

namespace iotdb { namespace util { namespace rwio {

template<class Stream, class Tp = bool>
struct impl {
    static std::optional<Tp> read(Stream& bstream) {
        std::optional <container_type> res = bstream.read_n(sizeof(Tp));
        if (!res) {
            return {};
        }
        return bconv::to<Tp>(res.value());
    }

    static size_t
    write(const Tp& data, Stream& stream) {
        return 0;
    }
};

template<class Stream>
struct impl<Stream, std::string> {
    static std::optional<std::string> read(Stream& bstream) {
        int32_t len = impl<Stream, int32_t>::read(bstream).value_or(-1);
        std::optional <container_type> res = bstream.read_n(len);
        if (!res) {
            return {};
        }
        return bconv::to<std::string>(res.value());
    }

    static size_t
    write(const std::string& data, Stream& stream) {
        return 0;
    }
};

/**( READ BASE TYPES )**/

template<typename Tp, typename InputStream>
std::optional<std::enable_if_t<!std::is_enum_v<Tp> && !std::is_array_v<Tp>, Tp>>
read(InputStream& bstream) {
    return impl<InputStream, Tp>::read(bstream);
}

/**( READ ENUMS )**/

template<typename Tp, typename InputStream>
std::optional<std::enable_if_t<std::is_enum_v<Tp>, Tp>>
read(InputStream& bstream) {
    std::optional <int16_t> res = read<int16_t>(bstream);
    if (!res) {
        return {};
    }
    return static_cast<Tp>(res.value());
}

/**( READ ARRAYS )**/

template<typename Tp, typename InputStream, typename T = std::remove_extent_t<Tp>>
std::vector<std::enable_if_t<std::is_array_v<Tp>, T>>
read(InputStream &bstream) {
    int32_t len = read<int32_t>(bstream).value_or(0);
    if (len <= 0) {
        return {};
    }
    std::vector <T> res;
    res.reserve(len);
    for (int i = 0; i < len; ++i) {
        res.push_back(read<T>(bstream).value());
    }
    return res;
}

/**( WRITE )**/

template<typename Tp, typename OutputStream>
size_t
write(const Tp& data, OutputStream& stream) {
    return impl<OutputStream, Tp>::write(data, stream);
}

}}}

#endif // IOTDB__RWIO__H
