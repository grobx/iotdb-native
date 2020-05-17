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
                static const std::string MAX_STRING_LENGTH = "max_string_length";
                static const std::string MAX_POINT_NUMBER = "max_point_number";
                abstract_encoder(): _type(iotdb::file::metadata::ts_encoding::PLAIN) {}
                abstract_encoder(const iotdb::file::metadata::ts_encoding& type,
                        const iotdb::tsfile::encoding::endian_type& endianess= iotdb::tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN)
                : _type(type), _endianess(endianess){}
                template<typename T> std::error_code &encode<T>(std::ostream &os) const {
                    return static_cast<const Kind *>(this)->encode<T>(os);
                }
                template<typename T> std::error_code &encode<T>(util::bytebuffer& buffer) const {
                    return static_cast<const Kind *>(this)->encode<T>(os);
                }
                void flush(util::bytebuffer& buffer) const {
                     static_cast<const Kind *>(this)->flush(util::bytebuffer& buffer);
                }
                void flush(std::ostream& os) const {
                    static_cast<const Kind *>(this)->flush(os);

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