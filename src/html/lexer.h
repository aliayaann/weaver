#pragma once
#include <string>
#include <vector>

enum class TokenType {
    TEXT,
    START_TAG,
    END_TAG,
    EOF_TOKEN // End of File
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(std::string input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos = 0;
    
    char current_char();
    void advance();
    bool is_eof();
};