#pragma once
#include <cstddef>

namespace eda {

class Node {
private:
    int value;
    Node* next;
public:
    explicit Node(int v) : value(v), next(nullptr) {}
    inline int getValue() const { return value; }
    inline void setValue(int v) { value = v; }
    inline Node* getNext() const { return next; }
    inline void setNext(Node* n) { next = n; }
};

} // namespace eda
