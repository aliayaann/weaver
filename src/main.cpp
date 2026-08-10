#include <iostream>
#include "html/lexer.h"

int main() {
    std::cout << "-- Weaver Web Engine --" << std::endl;

    // This is the raw HTML your browser receives from the internet
    std::string html = "<html><body><h1>Hello World</h1><p>This is my browser.</p></body></html>";
    
    Lexer lexer(html);
    std::vector<Token> tokens = lexer.tokenize();

    std::cout << "Tokens parsed:" << std::endl;
    for (const auto& token : tokens) {
        std::string type_str = "";
        switch (token.type) {
            case TokenType::TEXT: type_str = "TEXT"; break;
            case TokenType::START_TAG: type_str = "START_TAG"; break;
            case TokenType::END_TAG: type_str = "END_TAG"; break;
            case TokenType::EOF_TOKEN: type_str = "EOF"; break;
        }
        std::cout << "[" << type_str << "] " << token.value << std::endl;
    }

    return 0;
}