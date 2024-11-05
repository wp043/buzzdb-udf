#include "execution/expression_executor.h"
#include "execution/udf_manager.h"
#include "expression/function_expression.h"

namespace buzzdb {
namespace execution {

common::Value ExpressionExecutor::Evaluate(const expression::AbstractExpression *expr, const common::Tuple *tuple) {
    // Handle different expression types
    if (expr->GetExpressionType() == expression::ExpressionType::FUNCTION_CALL) {
        auto func_expr = static_cast<const expression::FunctionExpression*>(expr);
        // Evaluate arguments
        std::vector<common::Value> args;
        for (const auto &arg : func_expr->GetArguments()) {
            args.push_back(Evaluate(arg.get(), tuple));
        }
        // Get function pointer
        auto func_ptr = UDFManager::GetInstance().GetFunction(func_expr->GetFunctionName());
        if (!func_ptr) {
            throw std::runtime_error("Function not found: " + func_expr->GetFunctionName());
        }
        // Call the function
        return func_ptr(args);
    }
    // Handle other expression types...
}

} // namespace execution
} // namespace buzzdb
