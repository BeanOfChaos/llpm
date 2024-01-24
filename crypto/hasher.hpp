#include <stdexcept>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include <openssl/sha.h>

#ifndef LLPM_HASHER_HPP

using hash_fn_t = unsigned char * (*)(const unsigned char*, size_t, unsigned char*);

template <hash_fn_t F, size_t digest_len>
class Digest {
    public:
        Digest(const std::string& hex_string)
        {
            if (hex_string.length() != 2*digest_len)
            {
                std::cout << digest_len << " != " << hex_string.length() << std::endl;
                throw std::exception();
            }
            unsigned char *ptr = new unsigned char[digest_len];
            for (size_t i = 0; i < digest_len; i = i+2)
            {
                const char first = hex_string[i], second = hex_string[i+1];
                ptr[i] = ((first - u8'A') << 4) | ((second - u8'A') & 0x00ff);
            }
            buffer.reset(ptr);
        }
        Digest(unsigned char *src): buffer(src) {};
        Digest(): buffer(nullptr) {};
        std::string hex() const
        {
            std::stringstream hex_stream;
            for (unsigned i = 0; i < SHA256_DIGEST_LENGTH; ++i)
                hex_stream << std::hex << std::setfill('0') << std::setw(2) << int(buffer[i]); 
            return hex_stream.str();
        }
        std::shared_ptr<const unsigned char[]> hash() const
        {
            return buffer;
        }
        size_t length() const
        {
            return digest_len;
        }
        std::shared_ptr<const unsigned char[]> raw() const
        {
            return buffer;
        }

        const unsigned char& get (size_t idx) const
        {
            if (idx >= digest_len)
                throw std::out_of_range("ugh");
            return buffer.get()[idx];
        }
        const unsigned char& operator[](size_t idx) const
        {
            return get(idx);
        }
        bool equals(const Digest<F, digest_len>& other) const
        {
            for (size_t i = 0; i < digest_len; ++i)
                if (get(i) != other.get(i))
                    return false;
            return true;
        }
        bool operator==(const Digest& other) const
        {
            return equals(other);
        }
    private:
        std::shared_ptr<const unsigned char[]> buffer;
};


template <hash_fn_t F, size_t digest_len>
class Hasher {
    static_assert(static_cast<int>(digest_len) > 0);
    public:
        using Digest_t = Digest<F, digest_len>;
        static constexpr size_t hash_length = digest_len;
        Hasher(){};
        void update(const unsigned char *data, size_t len)
        {
            ss.write(reinterpret_cast<const char *>(data), static_cast<long>(len));
            clear_last();
        }
        void update(std::shared_ptr<const unsigned char[]> data, size_t len)
        {
            update(data.get(), len);
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
        Hasher<F, digest_len>& operator<<(std::string data)
        {
            update(data);
            return *this;
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
using SHA256_Digest = SHA256_Hasher::Digest_t;

#define LLPM_HASHER_HPP
#endif