#include "hasher.hpp"

template <hash_fn_t F, size_t key_len, size_t sig_len>
class Signature {
    using Hasher_t = Hasher<hash_fn_t, 0>;
}