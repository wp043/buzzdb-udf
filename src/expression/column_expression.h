#pragma once

#include "abstract_expression.h"
#include <string>

namespace buzzdb {
namespace expression {

class ColumnExpression : public AbstractExpression {
public:
    ColumnExpression(const std::string& column_name);

    common::Value Evaluate(const common::Tuple* tuple) const override;
    ExpressionType GetExpressionType() const override { return ExpressionType::COLUMN_REF; }

    const std::string& GetColumnName() const { return column_name_; }

    // Assuming we have a method to set column index after planning
    void SetColumnIndex(size_t index) { column_index_ = index; }
    size_t GetColumnIndex() const { return column_index_; }

private:
    std::string column_name_;
    size_t column_index_; // Index of the column in the tuple
};

} // namespace expression
} // namespace buzzdb
