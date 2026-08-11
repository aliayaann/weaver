#include <iostream>
#include "html/lexer.h"
#include "html/parser.h"

int main() {
    std::cout << "--  Weaver Web Engine --" << std::endl;

    // Raw HTML from the internet
    std::string html = "<html><body><h1>Hello World</h1><p>This is my browser.</p></body></html>";
    
    // Tokenizing
    Lexer lexer(html);
    std::vector<Token> tokens = lexer.tokenize();

    // Parse
    Parser parser(tokens);
    std::unique_ptr<ElementNode> dom_tree = parser.parse();

    // Printing the tree
    std::cout << "\n--- DOM Tree Generated ---" << std::endl;
    dom_tree->print(0);

    return 0;
}