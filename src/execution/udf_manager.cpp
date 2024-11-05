#include "execution/udf_manager.h"
#include "catalog/catalog.h"
#include <dlfcn.h>

namespace buzzdb {
namespace execution {

UDFManager& UDFManager::GetInstance() {
    static UDFManager instance;
    return instance;
}

UDFPointer UDFManager::GetFunction(const std::string &name) {
    std::lock_guard<std::mutex> lock(cache_mutex_);

    // Check cache first
    auto it = udf_cache_.find(name);
    if (it != udf_cache_.end()) {
        return it->second;
    }

    // Load from catalog
    auto udf_entry = catalog::Catalog::GetInstance().GetFunction(name);
    if (!udf_entry) {
        return nullptr;
    }

    // Load shared library
    void *handle = dlopen(udf_entry->library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Cannot load library: " + udf_entry->library_path);
    }

    // Get function pointer
    UDFPointer func_ptr = (UDFPointer)dlsym(handle, "ExecuteUDF");
    if (!func_ptr) {
        dlclose(handle);
        throw std::runtime_error("Cannot find symbol 'ExecuteUDF' in library: " + udf_entry->library_path);
    }

    // Cache and return
    udf_cache_[name] = func_ptr;
    return func_ptr;
}

} // namespace execution
} // namespace buzzdb
