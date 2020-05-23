
#ifndef IOTDB__TSFILE__UTILS__BLOOM_FILTER__H
#define IOTDB__TSFILE__UTILS__BLOOM_FILTER__H

#include <unordered_map>

#include <tsfile/file/metadata/device_metadata_index.h>
#include <util/bitset.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb { namespace tsfile { namespace utils {

class bloom_filter {
    class hash_function {
        int32_t _cap;
        int32_t _seed;

    public:
        hash_function(int32_t cap, int32_t seed): _cap{cap}, _seed{seed} {}

        int32_t hash(const char* /*str*/) { return 0; }
        // TODO: return Math.abs(Murmur128Hash.hash(value, seed)) % cap
    };

    using funcs_type = std::vector<std::unique_ptr<hash_function>>;

    static constexpr const int32_t MAXIMAL_HASH_FUNCTION_SIZE = 8;
    static constexpr const int32_t SEEDS[] = {5, 7, 11, 19, 31, 37, 43, 59};
    util::bitset _bits;
    int32_t _size;
    funcs_type::size_type _hash_function_size;
    funcs_type _func;

public:
    bloom_filter(util::buffer_window& bs, int32_t fs, int32_t hfs)
        : _bits{bs}
        , _size{fs}
        , _hash_function_size{static_cast<funcs_type::size_type>(std::max(MAXIMAL_HASH_FUNCTION_SIZE, hfs))}
        , _func{_hash_function_size}
    {
        for (funcs_type::size_type i = 0; i < _hash_function_size; i++) {
            _func[i] = std::make_unique<hash_function>(_size, SEEDS[i]);
        }
    }
};

}}}

#endif // IOTDB__TSFILE__UTILS__BLOOM_FILTER__H
