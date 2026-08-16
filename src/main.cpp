#include <iostream>
#include "html/lexer.h"
#include "html/parser.h"

int main() {
    std::cout << "--- My Browser Engine Started ---" << std::endl;

    // Real-world HTML with attributes!
    std::string html = R"(
        <html>
            <body>
                <h1 class="title" id="main-heading">Hello World</h1>
                <p>This is my browser.</p>
                <a href="https://example.com" target=_blank>Click me</a>
            </body>
        </html>
    )";
    
    Lexer lexer(html);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    std::unique_ptr<ElementNode> dom_tree = parser.parse();

    std::cout << "\n--- DOM Tree Generated ---" << std::endl;
    dom_tree->print(0);

    return 0;
}