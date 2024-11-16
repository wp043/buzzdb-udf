#pragma once

#include <vector>
#include "value.h"

namespace buzzdb {
namespace common {

class Tuple {
public:
    Tuple();
    Tuple(const std::vector<Value>& values);

    // Get the value at a specific column index
    const Value& GetValue(size_t column_idx) const;

    // Set the value at a specific column index
    void SetValue(size_t column_idx, const Value& value);

    // Get the number of values (columns) in the tuple
    size_t GetSize() const;

private:
    std::vector<Value> values_;
};

} // namespace common
} // namespace buzzdb
