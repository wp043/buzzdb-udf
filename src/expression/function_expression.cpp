#include "function_expression.h"
#include "../execution/expression_executor.h"
#include <stdexcept>

namespace buzzdb {
namespace expression {

FunctionExpression::FunctionExpression(const std::string& func_name,
                                       std::vector<std::unique_ptr<AbstractExpression>> arguments)
    : func_name_(func_name), arguments_(std::move(arguments)) {}

common::Value FunctionExpression::Evaluate(const common::Tuple* tuple) const {
    throw std::runtime_error("FunctionExpression::Evaluate should not be called directly.");
}

} // namespace expression
} // namespace buzzdb
