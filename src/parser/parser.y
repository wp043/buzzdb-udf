/* ... existing code ... */

expression:
    IDENTIFIER '(' argument_list ')'
    {
        // Create FunctionExpression
        std::vector<std::unique_ptr<buzzdb::expression::AbstractExpression>> args = $3;
        $$ = new buzzdb::expression::FunctionExpression($1, std::move(args));
    }
    | IDENTIFIER
    {
        // Assume it's a column reference
        $$ = new buzzdb::expression::ColumnExpression($1);
    }
    | /* other expressions */
    ;

/* ... existing code ... */
