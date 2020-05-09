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
#include <cstdint>
#include <mutex>
#include <utility>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <memory>
#include <optional>

namespace iotdb {
    namespace util {

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
            const size_t DEFAULT_SIZE = 256;
        public:
            typedef typename std::vector<T> internal_buffer;
            typedef T value_type;
            typedef typename internal_buffer::iterator iterator;
            typedef typename internal_buffer::const_iterator const_iterator;
            /**
             * forward iterator in the buffer
             * @return an interator
             */
            iterator begin() { return _bytes.begin(); }
            /**
             * iterator in the buffer
             * @return
             */
            iterator end() { return _bytes.end(); }
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
            bool is_readable() const;
            /**
             * Read as single bute
             * @return byte read from the buffer
             */
            uint8_t read();
            /**
             * read n elements and places than to a buffer
             * @param s buffer to put the data
             * @param n number of items
             */
            void read(char* s, std::streamsize n);
            /**
             *
             * @param c
             */
            void get (char& c);
            /**
             * Read all bytes
             * @return a list of bytes
             */
            std::vector<T> read_all();
            /**
             * Read at most n bytes
             * @param n number of bytes to read
             * @return a tuple containing a pointer to the data and the real number of bytes read
             */
            std::optional<std::vector<T>> read_n(size_t n);

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
        };
        typedef basic_bytebuffer<int8_t> bytebuffer;
        typedef basic_bytebuffer<uint8_t> ubytebuffer;
    }
}
#include "../../src/util/bytebuffer.cpp"
#endif //IOTDB_NATIVE_BYTEBUFFER_H
