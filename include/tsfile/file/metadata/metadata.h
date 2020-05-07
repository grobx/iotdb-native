//
// Created by jozoppi on 5/7/20.
//

#ifndef IOTDB_NATIVE_METADATA_H
#define IOTDB_NATIVE_METADATA_H
namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace metadata {
                enum class compression_type {
                    UNCOMPRESSED, SNAPPY, GZIP, LZO, SDT, PAA, PLA
                };
                enum class ts_datatype {
                    BOOLEAN, INT32, INT64, FLOAT, DOUBLE, TEXT
                };
                enum class ts_encoding {
                    PLAIN, PLAIN_DICTIONARY, RLE, DIFF, TS_2DIFF, BITMAP, GORILLA, REGULAR
                };
            }
        }
    }
}

#endif //IOTDB_NATIVE_METADATA_H
