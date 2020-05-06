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
#include "../../include/util/bytebuffer.h"
namespace iotdb {
    namespace util {
        bytebuffer::bytebuffer() {
            _bytes.reserve(256);
            _reader_index = 16;
            _writer_index = 128;
        }
        bytebuffer::bytebuffer(size_t n) {
            _bytes.reserve(n);
            _reader_index = n / 16;
            _writer_index = n / 2;
        }
        bytebuffer::bytebuffer(const std::initializer_list <uint8_t> &bytes) {
            auto dim = bytes.size();
            _bytes.reserve(dim*2);
            std:copy(bytes.begin(), bytes.end(), _bytes);
            _writer_index=dim;
            _reader_index=0;
        }
        void bytebuffer::discard_bytes() {
            _writer_index -= _reader_index;
            _reader_index = 0;
        }

        bool bytebuffer::is_readable() const {
            return (_reader_index <= _writer_index);
        }
        uint8_t bytebuffer::read() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            auto tmp = _bytes[_reader_index];
            _reader_index++;
            return tmp;
        }
        std::vector<uint8_t> bytebuffer::read_all() {
            if (writer_index <= _reader_index) {
                return std::vector<uint8_t>();
            }
            std::vector<uint8_t> array(_writer_index-_reader_index);
            for (auto i = _reader_index; i <=writer_index; ++i)
            {
                array.push_back(_bytes[i]);
            }
            return array;
        }
        std::tuple<std::unique_ptr<uint8_t>, size_t> bytebuffer::read_n(size_t n){
            if (writer_index - _reader_index > n) {
                return std::vector<uint8_t>();
            }
            std::vector<uint8_t> array(n);
            for (auto i = _reader_index; i <_reader_index+n; ++i)
            {
                array.push_back(_bytes[i]);
            }
            _reader_index+=n;
            return std::make_tuple(std::make_unique<uint8_t>(array.data()), n)
        }
        void bytebuffer::write(uint8_t buf) {
            std::lock_guard <std::mutex> lock(_buffermutex);
            if (_writer_index >= _bytes.capacity()) {
                auto capacity = _bytes.capacity();
                _bytes.resize(capacity * 2);
            }
            _writer_index+=1;
            _bytes[_writer_index++] = buf;
        }
        void bytebuffer::write(const uint8_t *buffer, size_t siz) {
        }

        void bytebuffer::ensure_space() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            _bytes.reserve(_bytes.capacity() * 2);
        }
        size_t bytebuffer::max_writable() const {
            return _bytes.capacity() - _writer_index;
        }
        const size_t bytebuffer::size() const {
            return _bytes.size();
        }
        const size_t bytebuffer::capacity() const {
            return _bytes.capacity();
        }
        const std::string bytebuffer::hex() const {
            const char code[]{"0123456789ABCDEF"};
            std::ostringstream out;
            for (auto &b : _bytes) {
                auto num = b / 16;
                auto rest = b % 16;
                out << code[num];
                out << code[rest];
            }
            return out.str();
        }
        bool bytebuffer::operator==(const bytebuffer::bytebuffer& bytebuffer) {
            return hex().compare(bytebuffer.hex()) == 0;
        }
        uint8_t &operator[](std::size_t idx) { return _bytes[idx]; }
        const uint8_t &operator[](std::size_t idx) const { return _bytes[idx]; }
    }
}