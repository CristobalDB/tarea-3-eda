#pragma once
#include "LinkedList.hpp"

// Pila basada en LinkedList (header-only)
template <typename T>
class Stack {
    LinkedList<T> list_;
public:
    void push(const T& v){ list_.push_front(v); }
    void push(T&& v){ list_.push_front(std::move(v)); }
    T pop(){ return list_.pop_front(); }
    T& top(){ return list_.front(); }
    const T& top() const{ return list_.front(); }
    bool empty() const{ return list_.empty(); }
    std::size_t size() const{ return list_.size(); }
    void clear(){ list_.clear(); }
};
