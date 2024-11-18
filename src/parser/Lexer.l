%{
#include "Parser.hpp"
#include <cstring>

void yyerror(const char *s);
%}

DIGIT       [0-9]
ID_START    [a-zA-Z_]
ID_CHAR     [a-zA-Z0-9_]
STRING      \"([^\\"]|\\.)*\"
WS          [ \t\r\n]+

%%

"CREATE"            { return CREATE; }
"FUNCTION"          { return FUNCTION; }
"AS"                { return AS; }
"RETURNS"           { return RETURNS; }
"SYMBOL"            { return SYMBOL; }

{ID_START}{ID_CHAR}* {
                        yylval.str = strdup(yytext);
                        return IDENTIFIER;
                    }

{STRING}            {
                        yylval.str = strdup(yytext);
                        return STRING_LITERAL;
                    }

"("                 { return '('; }
")"                 { return ')'; }
","                 { return ','; }
";"                 { return ';'; }

{WS}                { /* Skip whitespace */ }

.                   { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
