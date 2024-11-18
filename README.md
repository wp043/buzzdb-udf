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

## Running the Application

After compiling, you can run the BuzzDB application with UDF support:

```bash
./src/buzzdb_udf
```

You will see a prompt:

```
Welcome to BuzzDB with UDF support!
Enter SQL statements or 'exit' to quit.
buzzdb>
```

### Example Usage

1. **Register a UDF**

   At the `buzzdb>` prompt, enter:

   ```sql
   CREATE FUNCTION add_integers AS './src/udf_examples/libsample_udf.so' SYMBOL 'add_integers' RETURNS INT;
   ```

   You should see:

   ```
   UDF 'add_integers' registered successfully.
   ```

2. **Use the UDF in a Query**

   Since we don't have an actual database or tables implemented, we'll assume that the UDF execution is tested within the context of the application logic or via unit tests.

## Testing UDF Execution

In a full database implementation, you would use the UDF in SQL queries like:

```sql
SELECT add_integers(5, 10);
```

However, since this implementation focuses on UDF support, you can test UDF execution using the unit tests provided.

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