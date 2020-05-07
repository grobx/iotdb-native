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

#include "util/bytebuffer.h"
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
        bytebuffer::bytebuffer(const std::initializer_list <uint8_t> &l) {
            auto dim = l.size();
            _bytes.reserve(dim*2);
            _bytes.insert(_bytes.end(), l.begin(), l.end());
            _writer_index=dim;
            _reader_index=0;
        }
        void bytebuffer::discard_bytes() {
            _writer_index -= _reader_index;
            _reader_index = 0;
        }
        void bytebuffer::read(char* s, std::streamsize n) {
            auto data = read_n(n);
            std::memcpy(s, data->data(), n);
        }

        void bytebuffer::get (char& c) {
            auto v = read();
            c = static_cast<char>(v);
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
            if (_writer_index <= _reader_index) {
                return std::vector<uint8_t>();
            }
            std::vector<uint8_t> array(_writer_index-_reader_index);
            for (auto i = _reader_index; i <=_writer_index; ++i) {
                array.push_back(_bytes[i]);
            }
            return array;
        }
        std::optional<std::vector<uint8_t>> bytebuffer::read_n(size_t n){
            const size_t zero = 0;
            if (n < zero || _writer_index - _reader_index < n) {
                return {};
            }
            std::vector<uint8_t> array;
            array.reserve(n);
            for (auto i = _reader_index; i <_reader_index+n; ++i) {
                array.push_back(_bytes[i]);
            }
            _reader_index+=n;
            return array;
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
            std::lock_guard <std::mutex> lock(_buffermutex);
            _writer_index +=siz;
            if (_writer_index >= _bytes.capacity()) {
                _bytes.resize(_writer_index * 2);
            }
            for (size_t i = 0; i < siz; ++i) {
                _bytes.push_back(buffer[i]);
            }
        }
        void bytebuffer::ensure_space() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            _bytes.reserve(_bytes.capacity() * 2);
        }
        size_t bytebuffer::max_writable() const {
            return _bytes.capacity() - _writer_index;
        }
        size_t bytebuffer::size() const {
            return _bytes.size();
        }
        size_t bytebuffer::capacity() const {
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
        bool bytebuffer::operator==(const iotdb::util::bytebuffer& bytebuffer) {
            return hex().compare(bytebuffer.hex()) == 0;
        }
        uint8_t& bytebuffer::operator[](std::size_t idx) { return _bytes[idx]; }
        const uint8_t&  bytebuffer::operator[](std::size_t idx) const { return _bytes[idx]; }
    }
}
