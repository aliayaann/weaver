#include "parser.h"
#include <stack>
#include <cctype>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens), pos(0) {}

std::pair<std::string, std::map<std::string, std::string>> Parser::parse_tag(const std::string& raw_tag) {
    std::string tag_name;
    std::map<std::string, std::string> attrs;
    
    size_t i = 0;
    // 1. Extract tag name (skip leading whitespace)
    while(i < raw_tag.length() && std::isspace(raw_tag[i])) i++;
    size_t start = i;
    while(i < raw_tag.length() && !std::isspace(raw_tag[i])) i++;
    tag_name = raw_tag.substr(start, i - start);
    
    // 2. Extract attributes
    while(i < raw_tag.length()) {
        // Skip whitespace
        while(i < raw_tag.length() && std::isspace(raw_tag[i])) i++;
        if(i >= raw_tag.length()) break;
        
        // Read attribute name
        size_t key_start = i;
        while(i < raw_tag.length() && raw_tag[i] != '=' && !std::isspace(raw_tag[i])) i++;
        std::string key = raw_tag.substr(key_start, i - key_start);
        
        // Skip whitespace around '='
        while(i < raw_tag.length() && std::isspace(raw_tag[i])) i++;
        
        if(i < raw_tag.length() && raw_tag[i] == '=') {
            i++; // skip '='
            while(i < raw_tag.length() && std::isspace(raw_tag[i])) i++; // skip space after '='
            
            std::string val;
            // Handle quoted values like class="my-class"
            if(i < raw_tag.length() && (raw_tag[i] == '"' || raw_tag[i] == '\'')) {
                char quote = raw_tag[i];
                i++; // skip opening quote
                size_t val_start = i;
                while(i < raw_tag.length() && raw_tag[i] != quote) i++;
                val = raw_tag.substr(val_start, i - val_start);
                if(i < raw_tag.length()) i++; // skip closing quote
            } else {
                // Handle unquoted values like width=100
                size_t val_start = i;
                while(i < raw_tag.length() && !std::isspace(raw_tag[i])) i++;
                val = raw_tag.substr(val_start, i - val_start);
            }
            attrs[key] = val;
        } else {
            // Boolean attribute like <input disabled>
            if(!key.empty()) attrs[key] = "";
        }
    }
    
    return {tag_name, attrs};
}

std::unique_ptr<ElementNode> Parser::parse() {
    auto document = std::make_unique<ElementNode>("document");
    std::stack<ElementNode*> node_stack;
    node_stack.push(document.get());

    while (pos < tokens.size()) {
        Token token = tokens[pos];
        pos++;

        if (token.type == TokenType::EOF_TOKEN) break;

        if (token.type == TokenType::TEXT) {
            if (token.value.find_first_not_of(" \n\t\r") != std::string::npos) {
                node_stack.top()->children.push_back(
                    std::make_unique<TextNode>(token.value)
                );
            }
        } 
        else if (token.type == TokenType::START_TAG) {
            // Use C++17 structured binding to unpack the tag name and attributes
            auto [tag_name, attributes] = parse_tag(token.value);
            
            auto element = std::make_unique<ElementNode>(tag_name);
            element->attributes = attributes; // Inject the attributes into the DOM node
            
            ElementNode* raw_ptr = element.get();
            node_stack.top()->children.push_back(std::move(element));
            node_stack.push(raw_ptr);
        } 
        else if (token.type == TokenType::END_TAG) {
            if (node_stack.size() > 1) {
                node_stack.pop();
            }
        }
    }
    
    return document;
}