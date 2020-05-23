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
#include <util/bytebuffer.h>
#include <tsfile/file/metadata/metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace encoding {
            static const std::string MAX_STRING_LENGTH = "max_string_length";
            static const std::string MAX_POINT_NUMBER = "max_point_number";
            template<typename Kind>
            class abstract_decoder {
            public:
                abstract_decoder() {}
                explicit abstract_decoder(const file::ts_encoding& type, const endian_type _endian = endian_type::IOTDB_BIG_ENDIAN);
                const std::error_code decode(std::ostream &os) const;
                const std::error_code decode(util::bytebuffer& buffer) const;
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
            abstract_decoder<Kind>::abstract_decoder(const file::ts_encoding &type, const endian_type _endian): _encoding(type) {

            }

            template<typename Kind>
            endian_type abstract_decoder<Kind>::get_endian() const {
                return _endian;
            }

            template<typename Kind>
            file::ts_encoding abstract_decoder<Kind>::get_type() const {
                return _encoding;
            }

            template<typename Kind>
            void abstract_decoder<Kind>::set_type(const file::ts_encoding &type) {
                    _encoding = type;
            }

            template<typename Kind>
            const std::error_code abstract_decoder<Kind>::decode(std::ostream &os) const {
                return std::make_error_code(std::errc::function_not_supported);
            }

            template<typename Kind>
            const std::error_code abstract_decoder<Kind>::decode(util::bytebuffer &buffer) const {
                return std::make_error_code(std::errc::function_not_supported);
            }
        }
    }

#endif