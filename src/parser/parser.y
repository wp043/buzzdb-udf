%token CREATE FUNCTION RETURNS LIBRARY

%%
statement:
    // ... existing statements ...
    | create_function_stmt
    ;

create_function_stmt:
    CREATE FUNCTION identifier '(' opt_parameter_list ')' RETURNS data_type LIBRARY string_literal
    {
        $$ = new CreateFunctionStatement($3, $5, $7);
    }
;

// ... other grammar rules ...
