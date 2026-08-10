#include "lexer.h"

Lexer::Lexer(std::string input) : input(input), pos(0) {}

char Lexer::current_char() {
    if (is_eof()) return '\0';
    return input[pos];
}

void Lexer::advance() {
    pos++;
}

bool Lexer::is_eof() {
    return pos >= input.length();
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    
    // Loop through the entire HTML string
    while (!is_eof()) {
        if (current_char() == '<') {
            advance(); // skip the '<'
            bool is_end_tag = false;
            
            // Check if it's a closing tag like </html>
            if (!is_eof() && current_char() == '/') {
                is_end_tag = true;
                advance(); // skip the '/'
            }
            
            std::string tag_data = "";
            // Read until we hit the closing '>'
            while (!is_eof() && current_char() != '>') {
                tag_data += current_char();
                advance();
            }
            advance(); // skip the '>'
            
            if (is_end_tag) {
                tokens.push_back({TokenType::END_TAG, tag_data});
            } else {
                tokens.push_back({TokenType::START_TAG, tag_data});
            }
        } else {
            // If it's not a tag, it must be raw text
            std::string text = "";
            while (!is_eof() && current_char() != '<') {
                text += current_char();
                advance();
            }
            if (!text.empty()) {
                tokens.push_back({TokenType::TEXT, text});
            }
        }
    }
    
    tokens.push_back({TokenType::EOF_TOKEN, ""});
    return tokens;
}