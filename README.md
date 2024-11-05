# BuzzDB with User-Defined Functions (UDFs) Support

Welcome to BuzzDB enhanced with User-Defined Functions (UDFs) support. This extension allows users to write custom functions in C++, register them with the database, and use them seamlessly within SQL queries.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building BuzzDB](#building-buzzdb)
- [Developing UDFs](#developing-udfs)
  - [Writing a UDF](#writing-a-udf)
  - [Compiling a UDF](#compiling-a-udf)
  - [Registering a UDF](#registering-a-udf)
  - [Using a UDF in Queries](#using-a-udf-in-queries)
- [Testing](#testing)
- [Security Considerations](#security-considerations)
- [Documentation](#documentation)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction

BuzzDB is a relational database management system developed in C++. This version of BuzzDB introduces support for User-Defined Functions (UDFs), enabling users to extend the database's functionality by writing custom functions that can be invoked within SQL queries.

## Features

- **UDF Registration**: Easily register and manage UDFs within the database.
- **Seamless Integration**: Use UDFs in SQL queries just like built-in functions.
- **C++ Implementation**: Write UDFs in C++ for high performance.
- **Security Measures**: Sandbox environment to prevent unauthorized operations within UDFs.
- **Extensive Documentation**: Guides and examples to help you develop and use UDFs effectively.

## Getting Started

### Prerequisites

- **Operating System**: Linux or macOS (Unix-like environments)
- **Compiler**: GCC or Clang with C++11 support
- **Build Tools**: Make
- **Dependencies**:
  - Standard C++ libraries
  - POSIX libraries (for dynamic loading and threading)
  - [Bison](https://www.gnu.org/software/bison/) and [Flex](https://github.com/westes/flex) (for parsing)

### Building BuzzDB

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/jarulraj/buzzdb.git
   cd buzzdb
   ```

2. **Set Up the Environment** (optional):

   ```bash
   ./scripts/setup_environment.sh
   ```

3. **Build the Database**:

   ```bash
   make clean
   make
   ```

   This command will compile all the source files and generate the BuzzDB executable.

## Developing UDFs

### Writing a UDF

1. **Create a New UDF Source File**:

   Navigate to the `udf_examples/` directory:

   ```bash
   cd src/udf_examples/
   ```

   Create a new C++ file for your UDF, e.g., `my_custom_udf.cpp`.

2. **Implement the `ExecuteUDF` Function**:

   Your UDF must define an `extern "C"` function named `ExecuteUDF`:

   ```cpp
   #include "common/value.h"
   #include <vector>

   extern "C" buzzdb::common::Value ExecuteUDF(const std::vector<buzzdb::common::Value> &args) {
       // Your custom logic here
       // For example, return the product of integer arguments
       int product = 1;
       for (const auto &arg : args) {
           product *= arg.GetAs<int>();
       }
       return buzzdb::common::Value(product);
   }
   ```

3. **Handle Data Types**:

   Use the `buzzdb::common::Value` class to work with different data types. Make sure to handle type conversions and check for null values as needed.

### Compiling a UDF

1. **Use the Provided Makefile**:

   If you're in the `udf_examples/` directory, you can use the existing `Makefile`. Add your source file to the `Makefile`:

   ```Makefile
   UDFS = my_sum_udf.so my_custom_udf.so
   ```

2. **Compile the UDF**:

   ```bash
   make
   ```

   This command will compile your UDF source file into a shared library (e.g., `my_custom_udf.so`).

3. **Alternatively, Use the Build Script**:

   ```bash
   ../../scripts/build_udf.sh my_custom_udf.cpp
   ```

### Registering a UDF

1. **Start BuzzDB**:

   ```bash
   ./buzzdb
   ```

2. **Register the UDF with a SQL Command**:

   ```sql
   CREATE FUNCTION my_custom_udf(INTEGER, INTEGER) RETURNS INTEGER LIBRARY '/path/to/my_custom_udf.so';
   ```

   Replace `/path/to/my_custom_udf.so` with the actual path to your compiled shared library.

### Using a UDF in Queries

Once registered, you can use your UDF in SQL queries:

```sql
SELECT my_custom_udf(column1, column2) FROM my_table WHERE my_custom_udf(column3, column4) > 100;
```

## Testing

1. **Navigate to the Test Directory**:

   ```bash
   cd test/
   ```

2. **Build and Run Tests**:

   ```bash
   make clean
   make
   ./udf_test
   ```

   The tests will verify UDF registration, execution, and error handling.

## Security Considerations

- **Sandboxing**:

  UDFs are executed in a sandboxed environment to prevent unauthorized operations. The sandbox restricts system calls that can be made within UDFs.

- **Best Practices**:

  - Avoid performing file I/O, network operations, or other sensitive actions within UDFs.
  - Handle exceptions and errors gracefully to prevent crashes.
  - Validate input arguments within your UDF to ensure robustness.

- **Resource Usage**:

  Be mindful of the resources your UDF consumes. Avoid excessive memory allocations and long-running computations that could degrade database performance.

For more details, refer to the [Security Guidelines](docs/security_guidelines.md).

## Documentation

- **[UDF Development Guide](docs/udf_development_guide.md)**: Detailed instructions and examples for writing and using UDFs.
- **[Security Guidelines](docs/security_guidelines.md)**: Information on the security model and best practices for UDF development.

**Makefile**
---

**Explanation of the Makefile**

- **Variables**:
  - `CXX`, `CXXFLAGS`: Compiler settings.
  - `SRC_DIR`, `BUILD_DIR`, `BIN_DIR`, `TEST_DIR`, `UDF_EXAMPLES_DIR`: Directory paths.
  - `SRC_FILES`, `OBJ_FILES`: Source and object files for the main database.
  - `UDF_LIBS`: Shared library files for UDFs.
  - `TEST_SRC_FILES`, `TEST_OBJ_FILES`, `TEST_TARGET`: Source and object files for tests.

- **Targets**:
  - `all`: Default target that builds the database executable and UDFs.
  - `directories`: Ensures all necessary directories exist.
  - `$(TARGET)`: Builds the main BuzzDB executable.
  - `$(BUILD_DIR)/%.o`: Compiles source files to object files.
  - `$(UDF_EXAMPLES_DIR)/%.so`: Compiles UDF source files into shared libraries.
  - `test`: Builds and runs tests.
  - `clean`: Removes build artifacts.

- **Commands**:
  - Uses pattern rules to simplify compilation steps.
  - Includes necessary compiler flags and include paths.