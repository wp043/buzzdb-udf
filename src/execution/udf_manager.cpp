#include "udf_manager.h"

namespace buzzdb {
namespace execution {

UDFManager& UDFManager::GetInstance() {
    static UDFManager instance;
    return instance;
}

UDFPointer UDFManager::GetFunction(const std::string& name) {
    std::lock_guard<std::mutex> lock(cache_mutex_);

    auto it = udf_cache_.find(name);
    if (it != udf_cache_.end()) {
        return it->second;
    }

    auto& catalog = catalog::Catalog::GetInstance();
    auto udf_entry = catalog.GetFunction(name);
    if (!udf_entry) {
        return nullptr;
    }

    void* handle = dlopen(udf_entry->library_path.c_str(), RTLD_NOW);
    if (!handle) {
        throw std::runtime_error("Cannot load library: " + udf_entry->library_path);
    }

    UDFPointer func_ptr = (UDFPointer)dlsym(handle, "ExecuteUDF");
    if (!func_ptr) {
        dlclose(handle);
        throw std::runtime_error("Cannot find symbol 'ExecuteUDF' in library: " + udf_entry->library_path);
    }

    udf_cache_[name] = func_ptr;
    return func_ptr;
}

} // namespace execution
} // namespace buzzdb
