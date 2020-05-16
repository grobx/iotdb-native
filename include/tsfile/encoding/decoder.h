#ifndef ENCODER_H
#define ENCODER_H
#include <util/bytebuffer.h>
#include <tsfile/file/metadata/metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace encoding {

            template<typename Kind>
            class abstract_decoder {
            public:
                constexpr MAX_STRING_LENGTH = "max_string_length";
                constexpr MAX_POINT_NUMBER = "max_point_number";
                abstract_decoder(): _type(iotdb::file::metadata::ts_encoding::PLAIN) {}
                abstract_decoder(const iotdb::file::metadata::ts_encoding& type) : _type(type){}
                template<typename T> std::error_code &decode<T>(std::ostream &os) const {
                    return static_cast<const Kind *>(this)->encode<T>(os);
                }
                template<typename T> std::error_code &decode<T>(util::bytebuffer& buffer) const {
                    return static_cast<const Kind *>(this)->encode<T>(os);
                }
                iotdb::tsfile::encoding::endian_type get_endian() const {
                    return _endianess;
                }
                void set_endian(const iotdb::tsfile::encoding::endian_type& endian) {
                    _endianess = endian;
                }
                iotdb::file::metadata::ts_encoding get_type() const {
                    return _type;
                }
                void set_type(const iotdb::file::metadata::ts_encoding& type) {
                    _type = type;
                }
                void cleanup() {
                    static_cast<const Kind *>(this)->cleanup();
                }
            }
            private:
                iotdb::file::metadata::ts_encoding _type;
                iotdb::tsfile::encoding::endian_type _endianess;
            };
        }
    }

#endif