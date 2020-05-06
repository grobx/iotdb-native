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
#include <utility>
#include <string>
#include <algorithm>

namespace iotdb {
    namespace util {
        /**
        * bytebuffer is a thread safe class for a random and sequential accessible sequence of zero or more bytes (octets).
        * The design is based on netty's bytebuf. We use two indexes:
        * 1. ReaderIndex
        * 2. WriterIndex
        */
        class bytebuffer {
            std::vector <uint8_t> _bytes;
            size_t _reader_index = 0;
            size_t _writer_index = 0;
            std::mutex _buffermutex;
            const size_t DEFAULT_SIZE = 256;
        public:
            /**
             * default constructor
             */
            bytebuffer();
            /**
             * construct a byte array of predefined size
             * @param n number of bytes that a bytearray should have
             */
            bytebuffer(size_t n);
            /**
             * construct a byte array of predefined size using uniform init
             * @param n number of bytes that a bytearray should have
             */
            bytebuffer(const std::initializer_list<uint8_t>& bytes);
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
             * Read all bytes
             * @return a list of bytes
             */
            std::vector<uint8_t> read_all();
            /**
             * Read at most n bytes
             * @param n number of bytes to read
             * @return a tuple containing a pointer to the data and the real number of bytes read
             */
            std::tuple<std::unique_ptr<uint8_t>, size_t> read_n(size_t n);

            /**
             * Write a single byte
             * @param buf byte to write
             */
            void write(uint8_t buf);
            /**
             * Write a buffer of bytes
             * @param buffer buffer of bytes to be written
             * @param siz    size of the array
             */
            void write(const uint8_t *buffer, size_t siz);
            /**
             * Double the reserved size for the byte buffer
             */
            void ensure_space();
            /**
             * Fetch the max number of bytes
             * @return number of bytes
             */
            const size_t max_writable() const;
            /**
             * Get the size of the byte buffer
             * @return size in byte of the buffer
             */
            const size_t size() const;
            /**
             * Get the real capacitty of the buffer
             * @return
             */
            const size_t capacity() const;
            /**
             * Get the bytes converted in hexadecimal string
             * @return hexdecimal string of the bytebuffer
             */
            const std::string hex() const;
            /**
             * Compare if two byte buffers are the same
             */
            bool operator==(const bytebuffer &bytebuffer);
            /**
             * Return the byte by random access
             * @param idx index of the byte
             * @return value of the byte
             */
            uint8_t &operator[](std::size_t idx);
            /**
             * Return the byte by random access
             * @param idx index of the byte
             * @return value of the byte
             */
            const uint8_t &operator[](std::size_t idx) const;
        };
    }
}
#endif //IOTDB_NATIVE_BYTEBUFFER_H
