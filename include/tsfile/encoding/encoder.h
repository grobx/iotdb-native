#ifndef ENCODER_H
#define ENCODER_H
#include <util/bytebuffer.h>
#include <tsfile/file/metadata/metadata.h>

namespace iotdb {
    namespace tsfile {
        namespace encoding {

            template<typename Kind>
            class abstract_encoder {
            public:
                constexpr MAX_STRING_LENGTH = "max_string_length";
                constexpr MAX_POINT_NUMBER = "max_point_number";
                abstract_encoder(): _type(iotdb::file::metadata::ts_encoding::PLAIN) {}
                abstract_encoder(const iotdb::file::metadata::ts_encoding& type) : _type(type){}
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
            };
        }
    }

#endif