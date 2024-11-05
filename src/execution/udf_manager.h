#pragma once

#include <unordered_map>
#include <string>
#include <mutex>

namespace buzzdb {
namespace execution {

typedef common::Value (*UDFPointer)(const std::vector<common::Value> &args);

class UDFManager {
public:
    static UDFManager& GetInstance();

    UDFPointer GetFunction(const std::string &name);

private:
    UDFManager() {}
    std::unordered_map<std::string, UDFPointer> udf_cache_;
    std::mutex cache_mutex_;
};

} // namespace execution
} // namespace buzzdb
