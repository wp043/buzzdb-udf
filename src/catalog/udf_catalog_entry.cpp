#include "catalog/udf_catalog_entry.h"

namespace buzzdb {
namespace catalog {

UDFCatalogEntry::UDFCatalogEntry(const std::string &name,
                                 const std::string &return_type,
                                 const std::vector<std::string> &arg_types,
                                 const std::string &library_path)
    : name(name), return_type(return_type), arg_types(arg_types), library_path(library_path) {}

} // namespace catalog
} // namespace buzzdb
