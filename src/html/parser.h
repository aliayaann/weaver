#pragma once
#include <vector>
#include <memory>
#include <map>
#include <utility>
#include "lexer.h"
#include "dom.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    std::unique_ptr<ElementNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos = 0;
    
    // NEW: Returns both the tag name AND a map of attributes
    std::pair<std::string, std::map<std::string, std::string>> parse_tag(const std::string& raw_tag);
};