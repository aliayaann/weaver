#include "parser.h"
#include <stack>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), pos(0) {}

std::string Parser::extract_tag_name(const std::string& raw_tag) {
    // If the tag has spaces (like "div class='box'"), we only want "div"
    size_t space_pos = raw_tag.find(' ');
    if (space_pos == std::string::npos) {
        return raw_tag; 
    }
    return raw_tag.substr(0, space_pos);
}

std::unique_ptr<ElementNode> Parser::parse() {
    // 1. Create the absolute root of our tree
    auto document = std::make_unique<ElementNode>("document");
    
    // 2. Create a stack to keep track of nested tags
    std::stack<ElementNode*> node_stack;
    node_stack.push(document.get());

    // 3. Loop through all tokens
    while (pos < tokens.size()) {
        Token token = tokens[pos];
        pos++;

        if (token.type == TokenType::EOF_TOKEN) break;

        // A. Handle Raw Text
        if (token.type == TokenType::TEXT) {
            // Ignore pure empty whitespace/newlines for cleaner tree output
            if (token.value.find_first_not_of(" \n\t\r") != std::string::npos) {
                node_stack.top()->children.push_back(
                    std::make_unique<TextNode>(token.value)
                );
            }
        } 
        // B. Handle Opening Tags
        else if (token.type == TokenType::START_TAG) {
            std::string tag_name = extract_tag_name(token.value);
            auto element = std::make_unique<ElementNode>(tag_name);
            
            // We need a raw pointer to put in the stack, 
            // but unique_ptr retains ownership in the children vector!
            ElementNode* raw_ptr = element.get();
            
            // Add as child to the current parent, then make it the new parent
            node_stack.top()->children.push_back(std::move(element));
            node_stack.push(raw_ptr);
        } 
        // C. Handle Closing Tags
        else if (token.type == TokenType::END_TAG) {
            // Pop the current parent off the stack, returning to the previous parent
            // (Don't pop the root 'document' node!)
            if (node_stack.size() > 1) {
                node_stack.pop();
            }
        }
    }
    
    return document;
}