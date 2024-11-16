#pragma once

#include "abstract_expression.h"
#include <vector>
#include <string>
#include <memory>

namespace buzzdb {
namespace expression {

class FunctionExpression : public AbstractExpression {
public:
    FunctionExpression(const std::string& func_name,
                       std::vector<std::unique_ptr<AbstractExpression>> arguments);

    common::Value Evaluate(const common::Tuple* tuple) const override;
    ExpressionType GetExpressionType() const override { return ExpressionType::FUNCTION_CALL; }
    const std::string& GetFunctionName() const { return func_name_; }
    const std::vector<std::unique_ptr<AbstractExpression>>& GetArguments() const { return arguments_; }

private:
    std::string func_name_;
    std::vector<std::unique_ptr<AbstractExpression>> arguments_;
};

} // namespace expression
} // namespace buzzdb
