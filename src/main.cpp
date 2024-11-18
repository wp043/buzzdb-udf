#include <iostream>
#include "catalog/UDFCatalog.h"
#include "execution/UDFExecutor.h"
#include "parser/Parser.y"

void initializeSystem() {
}

void processStatement(const std::string& statement) {
    YY_BUFFER_STATE buffer = yy_scan_string(statement.c_str());
    yyparse();
    yy_delete_buffer(buffer);
}

int main() {
    initializeSystem();
    std::string line;
    std::cout << "Welcome to BuzzDB with UDF support!" << std::endl;
    std::cout << "Enter SQL statements or 'exit' to quit." << std::endl;

    while (true) {
        std::cout << "buzzdb> ";
        std::getline(std::cin, line);
        if (line == "exit") {
            break;
        }
        if (line.empty()) {
            continue;
        }
        try {
            processStatement(line);
        } catch (const std::exception& e) {
            std::cerr << "Error processing statement: " << e.what() << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
