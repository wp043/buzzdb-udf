#pragma once

#include "types.h"

namespace buzzdb {
namespace common {

class Value {
public:
    Value();
    Value(int integer_value);
    // Other constructors for different types

    int GetAsInt() const;
    // Other getters for different types

    // Type information
    TypeId GetTypeId() const;

private:
    TypeId type_id_;
    union {
        int integer_value_;
        // Other types
    } value_;
};

} // namespace common
} // namespace buzzdb
