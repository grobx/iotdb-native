
#include <tsfile/file/metadata/chunk_metadata.h>
#include <fstream>
namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace metadata {
                /**
                 *
                 * @param measurementUid
                 * @param datatype
                 * @param fileOffset
                 * @param stat
                 */
                chunk_metadata::chunk_metadata(const std::string &measurementUid,
                                               const ts_datatype &datatype,
                                               int64_t fileOffset,
                                               const statistics &stat) {

                }

                /**
                 *
                 * @param buffer
                 * @return
                 */
                std::error_code chunk_metadata::read_from(const iotdb::util::bytebuffer &buffer) {
                    return std::make_error_code(std::io_errc::stream);
                }

                /**
                 *
                 * @param stream
                 * @return
                 */
                std::error_code chunk_metadata::write_to(std::ostream &stream) {
                    return std::make_error_code(std::io_errc::stream);
                }

                /**
                 *

                std::ostream& chunk_metadata::operator<<(const metadata::chunk_metadata &p){
                    std::fstream fs;
                    return fs;
                }
                 */
            }
        }
    }
}
