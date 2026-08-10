#pragma once
#include <string>
#include <vector>
#include <memory>

// The base class for everything in the browser tree
class Node {
public:
    virtual ~Node() = default;
};

class TextNode : public Node {
public:
    std::string text;
    TextNode(std::string t) : text(t) {}
};

class ElementNode : public Node {
public:
    std::string tag_name;
    std::vector<std::unique_ptr<Node>> children;
    
    ElementNode(std::string tag) : tag_name(tag) {}
};