#ifndef UDF_EXECUTOR_H
#define UDF_EXECUTOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include "UDFCatalog.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    typedef HMODULE LibHandle;
    typedef FARPROC SymbolPtr;
#else
    #include <dlfcn.h>
    typedef void* LibHandle;
    typedef void* SymbolPtr;
#endif

class UDFExecutor {
public:
    static UDFExecutor& getInstance();

    void* executeUDF(const std::string& udf_name, const std::vector<void*>& args);

private:
    UDFExecutor() = default;
    std::unordered_map<std::string, LibHandle> library_handles;
    SymbolPtr loadSymbol(const UDFInfo& udf_info);
    LibHandle loadLibrary(const std::string& library_path);
    void unloadLibraries();
    ~UDFExecutor();
};

#endif
