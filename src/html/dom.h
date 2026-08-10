#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// The base class for everything in the browser tree
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
    std::vector<std::unique_ptr<Node>> children;
    
    ElementNode(std::string tag) : tag_name(tag) {}
    
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "<" << tag_name << ">\n";
        for (const auto& child : children) {
            child->print(indent + 2); // Indent children by 2 spaces
        }
        std::cout << std::string(indent, ' ') << "</" << tag_name << ">\n";
    }
};