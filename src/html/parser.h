#pragma once
#include <vector>
#include <memory>
#include "lexer.h"
#include "dom.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    std::unique_ptr<ElementNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos = 0;
    
    // Helper to strip attributes off tags (e.g. "div class='x'" -> "div")
    std::string extract_tag_name(const std::string& raw_tag); 
};