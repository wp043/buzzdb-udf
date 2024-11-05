#include "expression/function_expression.h"

namespace buzzdb {
namespace expression {

FunctionExpression::FunctionExpression(const std::string &func_name,
                                       std::vector<std::unique_ptr<AbstractExpression>> arguments)
    : func_name_(func_name), arguments_(std::move(arguments)) {}

} // namespace expression
} // namespace buzzdb
