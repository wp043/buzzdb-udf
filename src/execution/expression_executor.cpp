#include "expression_executor.h"
#include "udf_manager.h"
#include "../expression/function_expression.h"

namespace buzzdb {
namespace execution {

common::Value ExpressionExecutor::Evaluate(const expression::AbstractExpression* expr, const common::Tuple* tuple) {
    if (expr->GetExpressionType() == expression::ExpressionType::FUNCTION_CALL) {
        auto func_expr = static_cast<const expression::FunctionExpression*>(expr);
        std::vector<common::Value> args;
        for (const auto& arg : func_expr->GetArguments()) {
            args.push_back(Evaluate(arg.get(), tuple));
        }

        auto func_ptr = UDFManager::GetInstance().GetFunction(func_expr->GetFunctionName());
        if (!func_ptr) {
            throw std::runtime_error("Function not found: " + func_expr->GetFunctionName());
        }
        return func_ptr(args);
    }
    return common::Value(0);
}

} // namespace execution
} // namespace buzzdb
