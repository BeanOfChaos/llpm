#include <memory>
#include <ostream>
#include <vector>

#include <nlohmann/json.hpp>

#include "hasher.hpp"
#include "hmac.hpp"

#ifndef LLPM_DATABASE_HPP

class DatabaseEntry {
    private:
        const std::string _key;
        const std::string _value;
        const Signature<SHA256_Hasher> _signature;
    public:
        DatabaseEntry(const std::string& key, const std::string& value, const std::string& password);
        DatabaseEntry(const nlohmann::json& jdata);
        nlohmann::json JSON();
        std::string toString();
        const std::string& key();
        const std::string& value();
        const Signature<SHA256_Hasher> signature();
};

class Database {
    private:
        std::vector<DatabaseEntry> entries;
    public:
        static std::shared_ptr<Database> fromFile(const std::string& filename);
        static std::shared_ptr<Database> fromString(const std::string json);
        Database() noexcept;
        nlohmann::json JSON();
        std::string toString();
        DatabaseEntry get(const std::string& key);
        Database& insert(std::string key, std::string value, std::string password);
};

#define LLPM_DATABASE_HPP
#endif