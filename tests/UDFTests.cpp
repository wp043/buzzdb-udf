#include "TestUtils.h"
#include "UDFCatalog.h"
#include "UDFExecutor.h"
#include <cassert>
#include <iostream>

void testUDFRegistration() {
    UDFInfo udf_info;
    udf_info.name = "add_integers";
    udf_info.library_path = "./libsample_udf.so";
    udf_info.symbol_name = "add_integers";
    udf_info.return_type = "INT";
    bool success = UDFCatalog::getInstance().registerUDF(udf_info);
    assert(success);
}

void testUDFExecution() {
    int a = 5;
    int b = 10;
    std::vector<void*> args = { &a, &b };
    void* result = UDFExecutor::getInstance().executeUDF("add_integers", args);
    int res_value = *reinterpret_cast<int*>(result);
    assert(res_value == 15);
    delete reinterpret_cast<int*>(result);
}

int main() {
    testUDFRegistration();
    testUDFExecution();
    std::cout << "All UDF tests passed!" << std::endl;
    return 0;
}
