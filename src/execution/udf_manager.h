#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#ifdef __unix__
#include <dlfcn.h>
#endif
#include "../common/value.h"
namespace buzzdb {
namespace common {
    class Value;
}
}
#include "../catalog/catalog.h"

namespace buzzdb {
namespace execution {

class UDFManager {
public:
    typedef buzzdb::common::Value (*UDFPointer)(const std::vector<buzzdb::common::Value>& args);
    static UDFManager& GetInstance();
    UDFPointer GetFunction(const std::string& name);

private:
    UDFManager() {}
    std::unordered_map<std::string, UDFPointer> udf_cache_;
    std::mutex cache_mutex_;
};

} // namespace execution
} // namespace buzzdb