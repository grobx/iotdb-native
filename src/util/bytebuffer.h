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
#ifndef IOTDB_NATIVE_BYTEBUFFER_H
#define IOTDB_NATIVE_BYTEBUFFER_H
#include <vector>
#include <cstdlib>
#include <mutex>
#include <string>

namespace iotdb {
    namespace util {
        class bytebuffer {
            std::vector <uint8_t> _bytes;
            size_t _reader_index = 0;
            size_t _writer_index = 0;
            std::mutex _buffermutex;
            const size_t DEFAULT_SIZE = 256;
        public:
            bytebuffer() {
                _bytes.reserve(256);
                _reader_index = 16;
                _writer_index = 128;
            }

            bytebuffer(size_t n) {
                _bytes.reserve(n);
                _reader_index = n / 16;
                _writer_index = n / 2;
            }

            void discard_bytes() {
                _writer_index -= _reader_index;
                _reader_index = 0;
            }

            bool is_readable() const {
                return (_reader_index <= _writer_index);
            }

            uint8_t read() {
                std::lock_guard <std::mutex> lock(_buffermutex);
                auto tmp = _bytes[_reader_index];
                _reader_index++;
                return tmp;
            }

            void write(uint8_t buf) {
                std::lock_guard <std::mutex> lock(_buffermutex);
                if (_writer_index >= _bytes.capacity()) {
                    auto capacity = _bytes.capacity();
                    _bytes.resize(capacity * 2);
                }
                _bytes[_writer_index++] = buf;
            }

            void write(const uint8_t *buffer, size_t siz) {
                std::lock_guard <std::mutex> lock(_buffermutex);
                if (_writer_index + siz >= _bytes.capacity()) {
                    auto capacity = _bytes.capacity() + _writer_index + siz + 1;
                    _bytes.resize(capacity);
                }
                for (size_t i = 0; i < siz; ++i) {
                    _bytes.push_back(buffer[i]);
                    _writer_index++;
                }
            }

            void ensure_space() {
                std::lock_guard <std::mutex> lock(_buffermutex);
                _bytes.reserve(_bytes.capacity() * 2);
            }

            size_t max_writable() {
                return _bytes.capacity() - _writer_index;
            }

            const size_t size() const {
                return _bytes.size();
            }

            const size_t capacity() const {
                return _bytes.capacity();
            }

            const std::vector <uint8_t> bytes() const {
                return _bytes;
            }

            const std::string hex() const {
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

            bool operator==(const bytebuffer &bytebuffer) {
                return hex().compare(bytebuffer.hex()) == 0;
            }

            uint8_t &operator[](std::size_t idx) { return _bytes[idx]; }

            const uint8_t &operator[](std::size_t idx) const { return _bytes[idx]; }

        };

    }
}
#endif //IOTDB_NATIVE_BYTEBUFFER_H
