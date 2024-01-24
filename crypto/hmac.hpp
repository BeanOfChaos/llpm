#include "hasher.hpp"


#ifndef LLPM_HMAC_HPP

template<class T>
class Signature {
    private:
        typedef T hasher_t; 
        const static unsigned char opad = 0x5c;
        const static unsigned char ipad = 0x36;
        static constexpr int key_length = static_cast<int>(hasher_t::hash_length);
        hasher_t::Digest_t signature;

        static std::shared_ptr<unsigned char[]> pad_key(const unsigned char *pkey, size_t klen)
        {
            std::shared_ptr<unsigned char[]> ret(new unsigned char[hasher_t::hash_length]);
            if (klen <= hasher_t::hash_length)
                for (size_t i = 0; i < hasher_t::hash_length; ++i)
                    if (i < klen)
                        ret[static_cast<int>(i)] = pkey[static_cast<int>(i)];
                    else
                        ret[static_cast<int>(i)] = 0;
            else
            {
                hasher_t hasher;
                hasher.update(pkey, klen);
                auto digest = hasher.hash();
                for (size_t i = 0; i < hasher_t::hash_length; ++i)
                    ret[static_cast<int>(i)] = digest->get(i);              
            }
            return ret;
        }


    public:
        Signature(const unsigned char *msg, const unsigned char *pkey,
                  size_t mlen, size_t klen)
        {
            hasher_t hasher;
            auto padded_key = pad_key(pkey, klen);
            unsigned char outer_key[hasher_t::hash_length];
            unsigned char inner_key[hasher_t::hash_length];
            
            for (int i = 0; i < key_length; ++i)
            {
                outer_key[i] = padded_key[i] ^ opad;
                inner_key[i] = padded_key[i] ^ ipad;
            }
            hasher.update(inner_key, key_length);
            hasher.update(msg, mlen);
            auto inner_digest = hasher.hash();
            hasher.reset();
            hasher.update(outer_key, key_length);
            hasher.update(inner_digest->hash(), key_length);
            signature = *(hasher.hash().get());
        };
        Signature(const std::string msg, const unsigned char *pkey, size_t klen)
            : Signature(reinterpret_cast<const unsigned char*>(msg.c_str()), pkey, msg.length(), klen)  {}
        Signature(std::string hexvalue): signature(hexvalue) {};
        std::string toString() const
        {
            return signature.hex();
        };
        bool equals(const Signature& other) const
        {
          return this->signature == other.signature;  
        }
        bool operator==(const Signature& other) const
        {
            return equals(other);
        }
        bool operator!=(const Signature& other) const
        {
            return !equals(other);
        }
        bool verify(const unsigned char *msg, const unsigned char *pkey,
                    size_t mlen, size_t klen)
        {
            Signature other(msg, pkey, mlen, klen);
            return equals(other);
        }
        std::string hex()
        {
            return signature.hex();
        }
};


#define LLPM_HMAC_HPP
#endif