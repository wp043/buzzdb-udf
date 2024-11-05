#pragma once

#include <string>
#include <vector>

namespace buzzdb {
namespace catalog {

class UDFCatalogEntry {
public:
    UDFCatalogEntry(const std::string &name,
                    const std::string &return_type,
                    const std::vector<std::string> &arg_types,
                    const std::string &library_path);

    std::string name;
    std::string return_type;
    std::vector<std::string> arg_types;
    std::string library_path;
};

} // namespace catalog
} // namespace buzzdb
