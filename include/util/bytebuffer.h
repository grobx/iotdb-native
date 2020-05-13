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
#include <array>
#include <cstdlib>
#include <cstdint>
#include <mutex>
#include <utility>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <memory>
#include <optional>
#include <bitset>

#include <iotdb.h>
#include <tsfile/encoding/endian_type.h>

namespace iotdb {
    namespace util {

        typedef struct bitfield
        {
            unsigned first     : 1;
            unsigned second    : 1;
            unsigned third     : 1;
            unsigned fourth    : 1;
            unsigned fifth     : 1;
            unsigned six       : 1;
            unsigned seven     : 1;
            unsigned eight     : 1;
        } bitfield_t;

        typedef union  {
            int8_t byte;
            bitfield_t fields;
        } fbyte_t;

        /**
        * bytebuffer is a thread safe class for a random and sequential accessible sequence of zero or more bytes (octets).
        * The design is based on netty's bytebuf. We use two indexes:
        * 1. ReaderIndex
        * 2. WriterIndex
        */
        template <typename T> class basic_bytebuffer {
            std::vector<T> _bytes;
            size_t _reader_index = 0;
            size_t _writer_index = 0;
            std::mutex _buffermutex;
            tsfile::encoding::endian_type _order = tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN;
        public:
            typedef typename std::vector<T> internal_buffer;
            typedef T value_type;
            typedef typename internal_buffer::iterator iterator;
            typedef typename internal_buffer::reverse_iterator reverse_iterator;
            typedef typename internal_buffer::const_reverse_iterator const_reverse_iterator;
            typedef typename internal_buffer::const_iterator const_iterator;

            /**
             * default constructor
             */
            basic_bytebuffer();
            /**
             * construct a byte array of predefined size
             * @param n number of bytes that a bytearray should have
             */
            explicit basic_bytebuffer(size_t n);
            /**
             * construct a byte array of predefined size using uniform init
             * @param n number of bytes that a bytearray should have
             */
            basic_bytebuffer(const std::initializer_list<T>& bytes);
            /**
             * discard all files that has been read.
             */
            void discard_bytes();
            /**
             * Check if the buffer is readable
             * @return true if the reader index < writer index
             */
            bool is_readable() const noexcept ;

            /**
             * forward iterator in the buffer
             * @return an iterator to the beginning of the given container c
             */
            iterator begin() noexcept  { return _bytes.begin(); }
            /**
             * iterator in the buffer
             * @return an iterator to the end of the given container c
             */
            iterator end() noexcept { return _bytes.end(); }

            /**
             * iterator constant to the buffer
             * @return a constant iterator to the beginning of the given container c
             */
            const_iterator cbegin() const noexcept { return _bytes.cbegin(); }
            /**
             * iterator constant to the buffer
             * @return a constant iterator to the end of the buffer
             */
            const_iterator cend() const noexcept  { return  _bytes.cend(); }
            /**
             * reverse iterator to the begin of the buffer
             * @return reverse iterator to the end of the buffer
             */
            reverse_iterator rbegin() const noexcept { return _bytes.rbegin(); }
            /**
             * reverse iterator to the end of the buffer
             * @return reverse iterator to the end of the buffer
             */
            reverse_iterator rend() const noexcept  { return  _bytes.rend(); }
            /**
             * constant reverse iterator to the begin of the buffer
             * @return constant reverse iterator to the end of the buffer
             */
            const_reverse_iterator  crbegin() const noexcept { return _bytes.crbegin(); }
            /**
             * constant reverse iterator to the begin of the buffer
             * @return constant reverse iterator to the end of the buffer
             */
            const_reverse_iterator crend() const noexcept { return _bytes.crend(); }
            /**
             * Read as single byte
             * @return byte read from the buffer
             */
            T read();
            /**
             * read n elements and places than to a buffer
             * @param s buffer to put the data
             * @param n number of items
             */
            void read(T& s, std::streamsize n);
            /**
             * Read all bytes
             * @return a list of bytes
             */
            std::vector<T> read_all() const ;
            /**
             * Read at most n bytes
             * @param n number of bytes to read
             * @return data read
             */
            std::optional<std::vector<T>> read_n(size_t n);

            /**
             *
             * @return
             */

            bool has_remaining() const noexcept ;

            size_t remaining() const noexcept ;

            void set_order(const tsfile::encoding::endian_type& order);

            tsfile::encoding::endian_type order() const noexcept ;



            /**
             * Write a single byte
             * @param buf byte to write
             */
            void write(T buf);
            /**
             * Write a buffer of bytes
             * @param buffer buffer of bytes to be written
             * @param siz    size of the array
             */
            void write(const T *buffer, size_t siz);
            /**
             * Double the reserved size for the byte buffer
             */
            void ensure_space();
            /**
             * Fetch the max number of bytes
             * @return number of bytes
             */
            size_t max_writable() const;
            /**
             * Get the size of the byte buffer
             * @return size in byte of the buffer
             */
            size_t size() const;
            /**
             * Get the real capacitty of the buffer
             * @return
             */
            size_t capacity() const;
            /**
             * Get the bytes converted in hexadecimal string
             * @return hexdecimal string of the bytebuffer
             */
            const std::string hex() const;
            /**
             * Compare if two byte buffers are the same
             */
            bool operator==(const basic_bytebuffer<T> &bytebuffer);
            /**
             * Return the byte by random access
             * @param idx index of the byte
             * @return value of the byte
             */
            T &operator[](std::size_t idx);
            /**
             * Return the byte by random access
             * @param idx index of the byte
             * @return value of the byte
             */
            const T &operator[](std::size_t idx) const;

        private:
            void order_byte(int8_t & b, tsfile::encoding::endian_type& order) const noexcept;
        };
        typedef basic_bytebuffer<iotdb::value_type> bytebuffer;

    }
}
namespace iotdb {
    namespace util {
        template <typename T> basic_bytebuffer<T>::basic_bytebuffer() {
            _bytes.reserve(256);
            _reader_index = 16;
            _writer_index = 128;
        }
        template <typename T> basic_bytebuffer<T>::basic_bytebuffer(size_t n) : _bytes(n) {
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
        template <typename T> bool basic_bytebuffer<T>::has_remaining() const noexcept {
            return is_readable();
        }
        template <typename T> size_t basic_bytebuffer<T>::remaining() const noexcept {
            if  (_reader_index>=_writer_index) {
                return 0;
            }
            return _writer_index - _reader_index;
        }
        template <typename T> void basic_bytebuffer<T>::read(T& s, std::streamsize n) {
            auto data = read_n(n);
            std::memcpy(s, data.data(), n);
        }
        template <typename T> bool basic_bytebuffer<T>::is_readable() const noexcept {
            return (_reader_index <= _writer_index);
        }
        template <typename T> T basic_bytebuffer<T>::read() {
            std::lock_guard <std::mutex> lock(_buffermutex);
            auto tmp = _bytes[_reader_index];
            _reader_index++;
            return tmp;
        }
        template <typename T> std::vector<T> basic_bytebuffer<T>::read_all() const {
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
        template <typename T> void basic_bytebuffer<T>::set_order(const tsfile::encoding::endian_type& order) {
            _order =order;
            for (int i = 0; i < _bytes.size(); i++) {
                order_byte(_bytes[i], _order);
            }
        }
        template <typename T> tsfile::encoding::endian_type basic_bytebuffer<T>::order() const noexcept {
            return _order;
        }
        template <typename T> void basic_bytebuffer<T>::order_byte(int8_t & b,
                tsfile::encoding::endian_type& order) const noexcept {
            const int value { 0x01 };
            const void * address = static_cast<const void *>(&value);
            const unsigned char * least_significant_address = static_cast<const unsigned char *>(address);
            fbyte_t current_byte;
            fbyte_t result_byte;
            current_byte.byte = b;
            if (*least_significant_address == 0x01) {
                // the system is little_endian
                if (order == tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN) {
                    result_byte.fields.first = current_byte.fields.eight;
                    result_byte.fields.second = current_byte.fields.seven;
                    result_byte.fields.third = current_byte.fields.six;
                    result_byte.fields.fourth = current_byte.fields.fifth;
                    result_byte.fields.fifth = current_byte.fields.fourth;
                    result_byte.fields.six = current_byte.fields.third;
                    result_byte.fields.seven = current_byte.fields.second;
                    result_byte.fields.eight = current_byte.fields.first;
                }
            } else {
                // the system is big_endian
                if (order == tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN) {
                    result_byte.fields.first = current_byte.fields.eight;
                    result_byte.fields.second = current_byte.fields.seven;
                    result_byte.fields.third = current_byte.fields.six;
                    result_byte.fields.fourth = current_byte.fields.fifth;
                    result_byte.fields.fifth = current_byte.fields.fourth;
                    result_byte.fields.six = current_byte.fields.third;
                    result_byte.fields.seven = current_byte.fields.second;
                    result_byte.fields.eight = current_byte.fields.first;
                }
            }
            b = result_byte.byte;
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

        template<std::size_t N> std::bitset<N> to_bitset(const iotdb::util::bytebuffer& bytebuffer) {
            std::bitset<N> data;
            size_t j = 0;
            for (auto it = bytebuffer.cbegin(); it != bytebuffer.cend(); ++it) {
                fbyte_t current_byte;
                current_byte.byte = *it;
                for (int k = 0; k < 8; ++k) {
                    if (bytebuffer.order() == tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN) {
                            data.set(j, current_byte.fields.eight);
                            data.set(j+1, current_byte.fields.seven);
                            data.set(j+2, current_byte.fields.six);
                            data.set(j+3, current_byte.fields.fifth);
                            data.set(j+4, current_byte.fields.fourth);
                            data.set(j+5, current_byte.fields.third);
                            data.set(j+6, current_byte.fields.second);
                            data.set(j+7, current_byte.fields.first);
                    } else {
                        data.set(j, current_byte.fields.first);
                        data.set(j+1, current_byte.fields.second);
                        data.set(j+2, current_byte.fields.third);
                        data.set(j+3, current_byte.fields.fourth);
                        data.set(j+4, current_byte.fields.fifth);
                        data.set(j+5, current_byte.fields.six);
                        data.set(j+6, current_byte.fields.seven);
                        data.set(j+7, current_byte.fields.eight);
                    }
                }
                j+=8;
            }
            return data;
        }
        template<std::size_t N> std::array<int8_t ,N> to_array(const iotdb::util::bytebuffer& bytebuffer) {
            char *data = bytebuffer.read_all().data();
            std::array<int8_t, N> cdata = data;
            return cdata;
        }
    }
}
#endif //IOTDB_NATIVE_BYTEBUFFER_H
