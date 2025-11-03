#pragma once
#include "lLists/node.hpp"

namespace eda {

class Stack {
private:
    Node* head;
public:
    Stack();
    void push(int val);
    void push(Node* node);
    void pop();
    Node* top();
    bool isEmpty();
    void clear();
    virtual ~Stack();
};

} // namespace eda
