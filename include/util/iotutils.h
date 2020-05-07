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
#ifndef IOTDB_NATIVE_IO_UTILS_H
#define IOTDB_NATIVE_IO_UTILS_H

#include <iostream>
#include <string>

namespace iotdb {
    namespace util {
            struct concept buffered_data {

            };
            template <typename T> class readerwriter {
                typedef union {
                    char bytes[4];
                    int32_t int_value;
                } bytes2int;
                static std::string read_string(T& data) {
                }
                static int read_int(T& data) {
                    bytes2int tmp;
                    data.read(tmp.bytes, 4);
                    return data.int_value;
                }
                static bool read_bool(T& data) {
                    char a;
                    data.get(&a)
                    return a == 1;
                }
                static char read_byte()
                /**
                 * read a byte from byteBuffer.
                 */
            public static byte readByte(ByteBuffer buffer) {
                    return buffer.get();
                }

                /**
                 * read bytes array in given size
                 *
                 * @param buffer buffer
                 * @param size size
                 * @return bytes array
                 */
            public static byte[] readBytes(ByteBuffer buffer, int size) {
                    byte[] res = new byte[size];
                    buffer.get(res);
                    return res;
                }

            };
    }
}
#endif
