#pragma once
#include <string>

namespace buzzdb {
namespace parser {

// Parser class definition
class Parser {
public:
    Parser();
    ~Parser();

    void Parse(const std::string& query);
    // Other methods...
};

} // namespace parser
} // namespace buzzdb
