#include "catalog/catalog.h"
#include "execution/udf_manager.h"
#include "common/value.h"
#include <iostream>
#include <vector>
#include <cassert>

int main() {
    using namespace buzzdb;

    // Test UDF Registration
    catalog::UDFCatalogEntry udf_entry("my_sum_udf", "INTEGER", {"INTEGER", "INTEGER"}, "./src/udf_examples/my_sum_udf.so");
    bool registered = catalog::Catalog::GetInstance().CreateFunction(udf_entry);
    assert(registered);

    // Test UDF Retrieval
    auto retrieved_udf = catalog::Catalog::GetInstance().GetFunction("my_sum_udf");
    assert(retrieved_udf != nullptr);

    // Test UDF Execution
    auto udf_ptr = execution::UDFManager::GetInstance().GetFunction("my_sum_udf");
    assert(udf_ptr != nullptr);

    common::Value arg1(10);
    common::Value arg2(20);
    std::vector<common::Value> args = {arg1, arg2};
    common::Value result = udf_ptr(args);

    assert(result.GetAsInt() == 30);

    std::cout << "UDF Test Passed: 10 + 20 = " << result.GetAsInt() << std::endl;

    // Test Error Handling (Function Not Found)
    try {
        auto invalid_udf_ptr = execution::UDFManager::GetInstance().GetFunction("non_existent_udf");
        assert(invalid_udf_ptr == nullptr);
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }

    return 0;
}
