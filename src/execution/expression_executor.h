#pragma once

#include "../expression/abstract_expression.h"
#include "../common/tuple.h"
#include "../common/value.h"

namespace buzzdb {
namespace execution {

class ExpressionExecutor {
public:
    static common::Value Evaluate(const expression::AbstractExpression* expr, const common::Tuple* tuple);
};

} // namespace execution
} // namespace buzzdb
