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
        template<typename Tp>
        Tp to(iotdb::vbytes bytes) {
            Tp v;
            std::copy(bytes.rbegin(), bytes.rend(), (uint8_t*) &v);
            return v;
        }

        template<>
        bool to(iotdb::vbytes bytes) {
            return bytes[0] == 1u;
        }

        template<>
        std::string to(iotdb::vbytes bytes) {
            return std::string(bytes.begin(), bytes.end());
        }
    }
}

#endif // IOTDB_NATIVE_BCONV_H
