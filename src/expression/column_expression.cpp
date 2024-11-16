#include "column_expression.h"

namespace buzzdb {
namespace expression {

ColumnExpression::ColumnExpression(const std::string& column_name)
    : column_name_(column_name), column_index_(0) /* default index */ {}

common::Value ColumnExpression::Evaluate(const common::Tuple* tuple) const {
    // Retrieve the value from the tuple at the specified column index
    return tuple->GetValue(column_index_);
}

} // namespace expression
} // namespace buzzdb
