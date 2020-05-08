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
#ifndef IOTDB_NATIVE_BCONV_H
#define IOTDB_NATIVE_BCONV_H

#include <string>

#include "iotdb.h"

namespace iotdb {
    namespace bconv {
        int16_t to_short(iotdb::vbytes bytes) {
            int16_t s = 0;
            int16_t s0 = (int16_t) (bytes[1] & 0xff);
            int16_t s1 = (int16_t) (bytes[0] & 0xff);
            s1 <<= 8;
            s = (int16_t) (s0 | s1);
            return s;
        }

        int32_t to_int(iotdb::vbytes bytes) {
            return (bytes[3] & 0xFF)
                | (bytes[2] & 0xFF) << 8 | (bytes[1] & 0xFF) << 16 | (bytes[0] & 0xFF) << 24;
        }

        int64_t to_long(iotdb::vbytes bytes, int len) {
            int64_t num = 0;
            for (int ix = 0; ix < len; ix++) {
                num <<= 8;
                num |= (bytes[ix] & 0xff);
            }
            return num;
        }

        float_t to_float(iotdb::vbytes bytes) {
            float_t f;
            std::copy(bytes.rbegin(), bytes.rend(), (uint8_t*) &f);
            return f;
        }

        double_t to_double(iotdb::vbytes bytes) {
            double_t d;
            std::copy(bytes.rbegin(), bytes.rend(), (uint8_t*) &d);
            return d;
        }

        std::string to_string(iotdb::vbytes bytes) {
            return std::string(bytes.begin(), bytes.end());
        }
    }
}

#endif // IOTDB_NATIVE_BCONV_H
