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
#ifndef ENCODER_H
#define ENCODER_H
#include <string>
#include <util/bytebuffer.h>
#include <tsfile/file/metadata/metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace encoding {
            template<typename Kind>
            class abstract_encoder {
            public:
                abstract_encoder();
                explicit abstract_encoder(const file::ts_encoding& type, const endian_type endian = endian_type::IOTDB_BIG_ENDIAN);
                const std::error_code encode(std::ostream &os) const;
                const std::error_code &encode(util::bytebuffer& buffer) const;
                void flush(util::bytebuffer& buffer) const;
                void flush(std::ostream& os) const;
                endian_type get_endian() const;
                void set_endian(const endian_type& endian);
                file::ts_encoding get_type() const;
                void set_type(const file::ts_encoding& type);
                void cleanup();
            private:
                file::ts_encoding _encoding;
                endian_type _endian;
            };

            template<typename Kind>
            abstract_encoder<Kind>::abstract_encoder(): _encoding(file::ts_encoding::PLAIN), _endian(endian_type::IOTDB_BIG_ENDIAN) {
            }
            template<typename Kind>
            abstract_encoder<Kind>::abstract_encoder(const file::ts_encoding &type, endian_type endian):_encoding(type), _endian(endian) {
            }

            template<typename Kind>
            const std::error_code abstract_encoder<Kind>::encode(std::ostream &os) const {
                return std::error_code();
            }

            template<typename Kind>
            void abstract_encoder<Kind>::flush(util::bytebuffer &buffer) const {

            }

            template<typename Kind>
            void abstract_encoder<Kind>::flush(std::ostream &os) const {

            }

            template<typename Kind>
            endian_type abstract_encoder<Kind>::get_endian() const {
                return endian_type::IOTDB_BIG_ENDIAN;
            }

            template<typename Kind>
            file::ts_encoding abstract_encoder<Kind>::get_type() const {
                return file::ts_encoding::GORILLA;
            }

            template<typename Kind>
            void abstract_encoder<Kind>::set_type(const file::ts_encoding &type) {

            }

            template<typename Kind>
            void abstract_encoder<Kind>::cleanup() {

            }
        }
    }

#endif