%token CREATE FUNCTION AS RETURNS
%token IDENTIFIER STRING_LITERAL

%%

statement:
    create_function_statement
    | select_statement
    ;

create_function_statement:
    CREATE FUNCTION IDENTIFIER AS STRING_LITERAL SYMBOL STRING_LITERAL RETURNS IDENTIFIER {
        UDFInfo udf_info;
        udf_info.name = $3;
        udf_info.library_path = $5;
        udf_info.symbol_name = $7;
        udf_info.return_type = $9;
        UDFCatalog::getInstance().registerUDF(udf_info);
    }
    ;

function_call:
    IDENTIFIER '(' argument_list ')' {
    }
    ;

argument_list:
    ;

%%

