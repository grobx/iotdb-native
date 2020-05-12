//
// Created by jozoppi on 5/12/20.
//
#ifndef IOTDB_NATIVE_PAGE_HEADER_H
#define IOTDB_NATIVE_PAGE_HEADER_H
#include <tsfile/file/metadata/statistics.h>
namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace header {
                class page_header {
                public:
                    page_header(int uncompressed_size,
                            int compressed_size,
                            const iotdb::tsfile::file::metadata::statistics& stat,
                            bool modified);
                private:
                    int _uncompressed;
                    int _compressed_size;
                    iotdb::tsfile::file::metadata::statistics _statistics;
                    bool _modified;
                };
            }
        }
    }
}
#endif //IOTDB_NATIVE_PAGE_HEADER_H
