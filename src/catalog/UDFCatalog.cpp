#include "UDFCatalog.h"
#include <iostream>

UDFCatalog& UDFCatalog::getInstance() {
    static UDFCatalog instance;
    return instance;
}

bool UDFCatalog::registerUDF(const UDFInfo& udf_info) {
    if (udf_map.find(udf_info.name) != udf_map.end()) {
        std::cerr << "UDF '" << udf_info.name << "' already exists." << std::endl;
        return false;
    }
    udf_map[udf_info.name] = std::make_shared<UDFInfo>(udf_info);
    return true;
}

bool UDFCatalog::unregisterUDF(const std::string& udf_name) {
    auto it = udf_map.find(udf_name);
    if (it == udf_map.end()) {
        std::cerr << "UDF '" << udf_name << "' does not exist." << std::endl;
        return false;
    }
    udf_map.erase(it);
    return true;
}

std::shared_ptr<UDFInfo> UDFCatalog::getUDF(const std::string& udf_name) {
    auto it = udf_map.find(udf_name);
    if (it != udf_map.end()) {
        return it->second;
    }
    return nullptr;
}

void UDFCatalog::listUDFs() {
    for (const auto& pair : udf_map) {
        std::cout << "UDF Name: " << pair.second->name << std::endl;
    }
}
