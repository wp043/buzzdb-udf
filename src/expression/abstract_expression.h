#pragma once

#include <memory>
#include "../common/tuple.h"
#include "../common/value.h"

namespace buzzdb {
namespace expression {

enum class ExpressionType {
    INVALID,
    CONSTANT,
    COLUMN_REF,    // Added COLUMN_REF here
    FUNCTION_CALL,
    // Other expression types...
};

class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;

    // Evaluate the expression and return the result
    virtual common::Value Evaluate(const common::Tuple* tuple) const = 0;

    // Get the type of the expression
    virtual ExpressionType GetExpressionType() const = 0;
};

} // namespace expression
} // namespace buzzdb
