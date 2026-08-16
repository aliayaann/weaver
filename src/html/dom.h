#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>

class Node {
public:
    virtual ~Node() = default;
    virtual void print(int indent) const = 0;
};

class TextNode : public Node {
public:
    std::string text;
    TextNode(std::string t) : text(t) {}
    
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "Text: \"" << text << "\"\n";
    }
};

class ElementNode : public Node {
public:
    std::string tag_name;
    // NEW: A dictionary to store attributes like class="title"
    std::map<std::string, std::string> attributes; 
    std::vector<std::unique_ptr<Node>> children;
    
    ElementNode(std::string tag) : tag_name(tag) {}
    
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "<" << tag_name;
        
        // NEW: Print all attributes inside the tag
        for (const auto& [key, value] : attributes) {
            std::cout << " " << key << "=\"" << value << "\"";
        }
        std::cout << ">\n";
        
        for (const auto& child : children) {
            child->print(indent + 2);
        }
        std::cout << std::string(indent, ' ') << "</" << tag_name << ">\n";
    }
};