#include "UDFExecutor.h"
#include <iostream>

UDFExecutor& UDFExecutor::getInstance() {
    static UDFExecutor instance;
    return instance;
}

LibHandle UDFExecutor::loadLibrary(const std::string& library_path) {
    LibHandle handle = nullptr;

#if defined(_WIN32) || defined(_WIN64)
    handle = LoadLibraryA(library_path.c_str());
    if (!handle) {
        std::cerr << "Cannot load library: " << GetLastError() << std::endl;
    }
#else
    handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
    }
#endif

    return handle;
}

SymbolPtr UDFExecutor::loadSymbol(const UDFInfo& udf_info) {
    LibHandle handle = nullptr;
    auto it = library_handles.find(udf_info.library_path);
    if (it != library_handles.end()) {
        handle = it->second;
    } else {
        handle = loadLibrary(udf_info.library_path);
        if (!handle) {
            return nullptr;
        }
        library_handles[udf_info.library_path] = handle;
    }

    SymbolPtr symbol = nullptr;
#if defined(_WIN32) || defined(_WIN64)
    symbol = GetProcAddress(handle, udf_info.symbol_name.c_str());
    if (!symbol) {
        std::cerr << "Cannot load symbol: " << GetLastError() << std::endl;
    }
#else
    symbol = dlsym(handle, udf_info.symbol_name.c_str());
    if (!symbol) {
        std::cerr << "Cannot load symbol: " << dlerror() << std::endl;
    }
#endif

    return symbol;
}

void* UDFExecutor::executeUDF(const std::string& udf_name, const std::vector<void*>& args) {
    auto udf_info = UDFCatalog::getInstance().getUDF(udf_name);
    if (!udf_info) {
        std::cerr << "UDF '" << udf_name << "' not found." << std::endl;
        return nullptr;
    }

    SymbolPtr symbol = loadSymbol(*udf_info);
    if (!symbol) {
        return nullptr;
    }

    typedef int (*FuncType)(int, int);
#if defined(_WIN32) || defined(_WIN64)
    FuncType func = reinterpret_cast<FuncType>(symbol);
#else
    FuncType func = reinterpret_cast<FuncType>(symbol);
#endif

    int result = func(*reinterpret_cast<int*>(args[0]), *reinterpret_cast<int*>(args[1]));
    return new int(result);
}

void UDFExecutor::unloadLibraries() {
    for (auto& pair : library_handles) {
#if defined(_WIN32) || defined(_WIN64)
        FreeLibrary(pair.second);
#else
        dlclose(pair.second);
#endif
    }
    library_handles.clear();
}

UDFExecutor::~UDFExecutor() {
    unloadLibraries();
}
