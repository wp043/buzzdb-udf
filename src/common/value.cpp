#include "value.h"

namespace buzzdb {
namespace common {

Value::Value() : type_id_(TypeId::INVALID) {}

Value::Value(int integer_value) : type_id_(TypeId::INTEGER) {
    value_.integer_value_ = integer_value;
}

int Value::GetAsInt() const {
    if (type_id_ != TypeId::INTEGER) {
        throw std::runtime_error("Value type is not INTEGER");
    }
    return value_.integer_value_;
}

TypeId Value::GetTypeId() const {
    return type_id_;
}

} // namespace common
} // namespace buzzdb
