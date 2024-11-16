#pragma once

#include <unordered_map>
#include <string>
#include "udf_catalog_entry.h"

namespace buzzdb {
namespace catalog {

class Catalog {
public:
    static Catalog& GetInstance();

    bool CreateFunction(const UDFCatalogEntry& udf_entry);
    UDFCatalogEntry* GetFunction(const std::string& name);
    bool DropFunction(const std::string& name);

private:
    Catalog() {}
    std::unordered_map<std::string, UDFCatalogEntry> udf_map_;
};

} // namespace catalog
} // namespace buzzdb
