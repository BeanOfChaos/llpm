#include <fstream>
#include <iostream>
#include <sstream>

#include "database.hpp"

using nlohmann::json;


DatabaseEntry::DatabaseEntry(const std::string& key, const std::string& value, const std::string& password)
    : _key(key), _value(value), _signature(key + value, reinterpret_cast<const unsigned char*>(password.c_str()), password.length()) {}


DatabaseEntry::DatabaseEntry(const json& data)
: _key(data["key"]), _value(data["value"]), _signature(data["signature"])
{}

json DatabaseEntry::JSON()
{
    json out;
    out["key"] = _key;
    out["value"] = _value;
    out["signature"] = _signature.toString();
    return out;
}

std::string DatabaseEntry::toString()
{
    return JSON().dump();
}

const std::string& DatabaseEntry::key()
{
    return _key;
}
const std::string& DatabaseEntry::value()
{
    return _value;
};
const Signature<SHA256_Hasher> DatabaseEntry::signature()
{
    return _signature;
};

Database::Database() noexcept{}

json Database::JSON()
{
    json out ;
    std::vector<json> vec;
    for (auto& entry: entries)
    {
        vec.push_back(entry.JSON());
    }
    out["entries"] = vec;
    return out;
}

std::string Database::toString()
{
    return JSON().dump();
}


Database& Database::insert(std::string key, std::string value, std::string password)
{
    DatabaseEntry entry(key, value, password);
    entries.push_back(entry);
    return *this;
};

std::shared_ptr<Database> Database::fromFile(const std::string& filename)
{
    std::ifstream fs;
    std::stringstream ss;
    fs.open(filename);
    if (fs.is_open())
    {
        ss << fs.rdbuf();
    }
    return fromString(ss.str());
};

DatabaseEntry Database::get(const std::string& key)
{
    for (auto& entry: entries)
    {
        if (entry.key() == key)
            return entry;
    }
    throw std::exception();
};


std::shared_ptr<Database> Database::fromString(const std::string sjson)
{
    auto db = std::make_shared<Database>();
    json data = json::parse(sjson);
    for (auto& jentry: data["entries"])
    {
        DatabaseEntry entry(jentry);
        db->entries.push_back(entry);
    }
    return db;
};