#include "tuple.h"
#include <cstddef>

namespace buzzdb {
namespace common {

Tuple::Tuple() {}

Tuple::Tuple(const std::vector<Value>& values) : values_(values) {}

const Value& Tuple::GetValue(size_t column_idx) const {
    return values_.at(column_idx);
}

void Tuple::SetValue(size_t column_idx, const Value& value) {
    if (column_idx >= values_.size()) {
        values_.resize(column_idx + 1);
    }
    values_[column_idx] = value;
}

size_t Tuple::GetSize() const {
    return values_.size();
}

} // namespace common
} // namespace buzzdb
