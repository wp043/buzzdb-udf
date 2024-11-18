#ifndef UDF_CATALOG_H
#define UDF_CATALOG_H

#include <string>
#include <unordered_map>
#include <memory>

struct UDFInfo {
    std::string name;
    std::string library_path;
    std::string symbol_name;
    std::string return_type;
};

class UDFCatalog {
public:
    static UDFCatalog& getInstance();

    bool registerUDF(const UDFInfo& udf_info);
    bool unregisterUDF(const std::string& udf_name);
    std::shared_ptr<UDFInfo> getUDF(const std::string& udf_name);
    void listUDFs();

private:
    UDFCatalog() = default;
    std::unordered_map<std::string, std::shared_ptr<UDFInfo>> udf_map;
};

#endif
