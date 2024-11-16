# UDF Development Guide

## Writing a UDF

1. **Create a New Source File**

   In the `src/udf_examples/` directory, create a new C++ source file for your UDF, e.g., `my_custom_udf.cpp`.

2. **Implement the `ExecuteUDF` Function**

   Your UDF must define an `extern "C"` function named `ExecuteUDF` that returns a `buzzdb::common::Value` and accepts a `std::vector<buzzdb::common::Value>` as arguments.

   ```cpp
   #include "common/value.h"
   #include <vector>

   extern "C" buzzdb::common::Value ExecuteUDF(const std::vector<buzzdb::common::Value>& args) {
       // Your custom logic
   }
