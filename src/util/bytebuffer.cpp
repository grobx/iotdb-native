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

#include <util/bytebuffer.h>
namespace iotdb {
    namespace util {
        template <typename T> basic_bytebuffer<T>::basic_bytebuffer() {
            _bytes.reserve(256);
            _reader_index = 16;
            _writer_index = 128;
        }
        template <typename T> basic_bytebuffer<T>::basic_bytebuffer(size_t n) {
            _bytes.reserve(n);
            _reader_index = n / 16;
            _writer_index = n / 2;
        }
        template <typename T> basic_bytebuffer<T>::basic_bytebuffer(const std::initializer_list <T> &l) {
            auto dim = l.size();
            _bytes.reserve(dim*2);
            _bytes.insert(_bytes.end(), l.begin(), l.end());
            _writer_index=dim;
            _reader_index=0;
        }
        template <typename T> void basic_bytebuffer<T>::discard_bytes() {
            _writer_index -= _reader_index;
            _reader_index = 0;
        }
        template <typename T> void basic_bytebuffer<T>::read(char* s, std::streamsize n) {
            auto data = read_n(n);
            std::memcpy(s, data->data(), n);
        }

        template <typename T> void basic_bytebuffer<T>::get (char& c) {
            auto v = read();
            c = static_cast<char>(v);
        }
        template <typename T> bool basic_bytebuffer<T>::is_readable() const {
            return (_reader_index <= _writer_index);
        }
        template <typename T> uint8_t basic_bytebuffer<T>::read() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            auto tmp = _bytes[_reader_index];
            _reader_index++;
            return tmp;
        }
        template <typename T> std::vector<T> basic_bytebuffer<T>::read_all() {
            if (_writer_index <= _reader_index) {
                return std::vector<T >();
            }
            std::vector<T> array(_writer_index-_reader_index);
            for (auto i = _reader_index; i <=_writer_index; ++i) {
                array.push_back(_bytes[i]);
            }
            return array;
        }
        template <typename T> std::optional<std::vector<T>> basic_bytebuffer<T>::read_n(size_t n){
            const size_t zero = 0;
            if (n < zero || _writer_index - _reader_index < n) {
                return {};
            }
            std::vector<T> array;
            array.reserve(n);
            for (auto i = _reader_index; i <_reader_index+n; ++i) {
                array.push_back(_bytes[i]);
            }
            _reader_index+=n;
            return array;
        }
        template <typename T> void basic_bytebuffer<T>::write(T buf) {
            std::lock_guard <std::mutex> lock(_buffermutex);
            if (_writer_index >= _bytes.capacity()) {
                auto capacity = _bytes.capacity();
                _bytes.resize(capacity * 2);
            }
            _writer_index+=1;
            _bytes[_writer_index++] = buf;
        }
        template <typename T> void basic_bytebuffer<T>::write(const T *buffer, size_t siz) {
            std::lock_guard <std::mutex> lock(_buffermutex);
            _writer_index +=siz;
            if (_writer_index >= _bytes.capacity()) {
                _bytes.resize(_writer_index * 2);
            }
            for (size_t i = 0; i < siz; ++i) {
                _bytes.push_back(buffer[i]);
            }
        }
        template <typename T> void basic_bytebuffer<T>::ensure_space() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            _bytes.reserve(_bytes.capacity() * 2);
        }
        template <typename T> size_t basic_bytebuffer<T>::max_writable() const {
            return _bytes.capacity() - _writer_index;
        }
        template <typename T> size_t basic_bytebuffer<T>::size() const {
            return _bytes.size();
        }
        template <typename T> size_t basic_bytebuffer<T>::capacity() const {
            return _bytes.capacity();
        }
        template <typename T> const std::string basic_bytebuffer<T>::hex() const {
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
        template <typename T> bool basic_bytebuffer<T>::operator==(const iotdb::util::basic_bytebuffer<T>& bytebuffer) {
            return hex().compare(bytebuffer.hex()) == 0;
        }
        template <typename T>  T& basic_bytebuffer<T>::operator[](std::size_t idx) { return _bytes[idx]; }
        template <typename T> const T&  basic_bytebuffer<T>::operator[](std::size_t idx) const { return _bytes[idx]; }
    }
}
