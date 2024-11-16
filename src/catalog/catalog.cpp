#include "catalog.h"

namespace buzzdb {
namespace catalog {

Catalog& Catalog::GetInstance() {
    static Catalog instance;
    return instance;
}

bool Catalog::CreateFunction(const UDFCatalogEntry& udf_entry) {
    if (udf_map_.find(udf_entry.name) != udf_map_.end()) {
        return false;
    }
    udf_map_[udf_entry.name] = udf_entry;
    return true;
}

UDFCatalogEntry* Catalog::GetFunction(const std::string& name) {
    auto it = udf_map_.find(name);
    if (it != udf_map_.end()) {
        return &(it->second);
    }
    return nullptr;
}

bool Catalog::DropFunction(const std::string& name) {
    return udf_map_.erase(name) > 0;
}

} // namespace catalog
} // namespace buzzdb
