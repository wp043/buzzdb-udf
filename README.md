# Implementing User-Defined Functions (UDFs) in BuzzDB

This repository contains the implementation of User-Defined Functions (UDFs) in BuzzDB, allowing users to create, register, and execute custom functions within their SQL queries.

## Introduction

This project enhances BuzzDB by introducing support for scalar User-Defined Functions (UDFs) written in C++. Users can define custom functions, register them with BuzzDB, and use them within SQL queries as they would with built-in functions.

## File Structure

```
├── src
│   ├── catalog
│   │   ├── UDFCatalog.h
│   │   └── UDFCatalog.cpp
│   ├── execution
│   │   ├── UDFExecutor.h
│   │   └── UDFExecutor.cpp
│   ├── parser
│   │   ├── Parser.y
│   │   └── Lexer.l
│   ├── udf_examples
│   │   ├── sample_udf.h
│   │   ├── sample_udf.cpp
│   │   └── MakeFile
│   ├── main.cpp
│   └── Makefile
├── tests
│   ├── UDFTests.cpp
│   ├── TestUtils.h
│   └── Makefile
├── README.md
└── Makefile
```

## Installation and Compilation

### Prerequisites

- Compiler: C++17 compatible compiler (e.g., GCC 9.0+ or Clang 10.0+)
- Build Tools: GNU Make
- Parsing Tools: Flex and Bison
- Dynamic Loading Library: dl (usually included with standard libraries)
- Optional Libraries: Boost libraries (if needed for advanced features)

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/wp043/buzzdb-udf.git
   cd buzzdb-udf
   ```

2. **Compile BuzzDB with UDF Support**

   ```bash
   make
   ```
   This will compile the source code in the `src` directory and produce the buzzdb_udf executable.

3. **Compile Sample UDFs**

   ```bash
   cd src/udf_examples
   make
   ```
   This will create a shared library `libsample_udf.so` that can be registered with BuzzDB.


## Usage

### Defining a UDF

Users can define UDFs by creating C++ functions with a specific signature. Here's an example:

**`sample_udf.h`**

```cpp
#ifndef SAMPLE_UDF_H
#define SAMPLE_UDF_H

extern "C" {
    int add_integers(int a, int b);
    double multiply_doubles(double x, double y);
}

#endif
```

**`sample_udf.cpp`**

```cpp
#include "sample_udf.h"

extern "C" {

int add_integers(int a, int b) {
    return a + b;
}

double multiply_doubles(double x, double y) {
    return x * y;
}

}
```

Compile the UDF into a shared library:

```bash
make
```
This will generate `libsample_udf.so in` the `src/udf_examples` directory.


### Registering a UDF

Use the `CREATE FUNCTION` statement in BuzzDB to register the UDF:

```sql
CREATE FUNCTION add_integers AS 'path/to/libsample_udf.so' SYMBOL 'add_integers' RETURNS INT;

CREATE FUNCTION multiply_doubles AS 'path/to/libsample_udf.so' SYMBOL 'multiply_doubles' RETURNS DOUBLE;
```

This command adds the UDF to BuzzDB's catalog, making it available for use in queries.

### Using a UDF in Queries

Once registered, you can use the UDF in your SQL queries:

```sql
SELECT add_integers(column1, column2) FROM table_name;

SELECT multiply_doubles(column3, 2.5) FROM table_name WHERE column4 > 100;
```

## Testing

Unit tests are provided in the `tests` directory. To run the tests:

1. **Compile the Test Suite**

   ```bash
   cd tests
   make
   ```

2. **Run the Tests**

   ```bash
   ./udf_tests
   ```

The tests cover registration, execution, error handling, and security aspects of UDFs.

## Future Work

- **Table-Valued UDFs:** Extend support to UDFs that return tables.
- **Language Support Expansion:** Allow UDFs to be written in languages like Python or JavaScript.
- **Enhanced Optimization:** Improve the query optimizer to better handle UDFs.
- **Security Enhancements:** Implement code signing and more granular resource controls.

## License

This project is licensed under the MIT License.

# Notes

- **Security Considerations:** The implementation includes basic sandboxing using dynamic loading with `dlopen` and symbol resolution with `dlsym`. For enhanced security, consider integrating with security frameworks or sandboxing tools like Seccomp or SELinux.
- **Error Handling:** The code includes basic error handling with `std::cerr`. For a production system, integrate with BuzzDB's logging and error management facilities.
- **Thread Safety:** The current implementation does not account for thread safety in a multi-threaded environment. Synchronization mechanisms may be necessary.
- **Type Handling:** The example assumes specific function signatures. A robust implementation should handle various data types and signatures dynamically.