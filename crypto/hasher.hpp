#include <functional>
#include <memory>
#include <sstream>
#include <openssl/sha.h>


using hash_fn_t = unsigned char * (*)(const unsigned char*, size_t, unsigned char*);

template <hash_fn_t F, size_t digest_len>
class Digest {
    public:
        Digest(unsigned char *src): buffer(src) {};
        std::string hex()
        {
            std::stringstream hex_stream;
            for (unsigned i = 0; i < SHA256_DIGEST_LENGTH; ++i)
                hex_stream << std::hex << int(buffer[i]); 
            return hex_stream.str();
        }
        std::shared_ptr<const unsigned char[]> hash()
        {
            return buffer;
        }
        size_t length()
        {
            return digest_len;
        }
        std::shared_ptr<const unsigned char[]> raw()
        {
            return buffer;
        }
    private:
        std::shared_ptr<const unsigned char[]> buffer;
};


template <hash_fn_t F, size_t digest_len>
class Hasher {
    using Digest_t = Digest<F, digest_len>;
    public:
        Hasher(){};
        void update(const unsigned char *data, size_t len)
        {
            ss.write(reinterpret_cast<const char *>(data), static_cast<long>(len));
            clear_last();
        }
        void update(const signed char *data, size_t len)
        {
            ss.write(reinterpret_cast<const char *>(data), static_cast<long>(len)); 
            clear_last();
        }
        void update(std::string data)
        {
            ss << data;
            clear_last();
        }
        void reset()
        {
            ss.clear();
            clear_last();
        }
        std::shared_ptr<Digest_t> hash()
        {
            if (last_hash)
                return last_hash;
            std::string s = ss.str();
            unsigned char *buffer = new unsigned char[digest_len];
            F(reinterpret_cast<const unsigned char*>(s.c_str()), s.length(), buffer);
            auto ret = std::make_shared<Digest_t>(buffer);
            last_hash = ret;
            return ret;
        }
        void rehash()
        {
            auto h = this->hash();
            reset();
            update(h->raw().get(), digest_len);
        }
    private:
        std::stringstream ss;
        std::shared_ptr<Digest_t> last_hash;
        void clear_last()
        {
            last_hash.reset();
        }
};

using SHA256_Hasher = Hasher<SHA256, SHA256_DIGEST_LENGTH>;
