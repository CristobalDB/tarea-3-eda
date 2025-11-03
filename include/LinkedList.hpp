#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

// Lista enlazada simple header-only (C++11)
template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& v, Node* n=nullptr): value(v), next(n) {}
        explicit Node(T&& v, Node* n=nullptr): value(std::move(v)), next(n) {}
    };
    Node* head_;
    std::size_t size_;
public:
    LinkedList(): head_(nullptr), size_(0) {}
    ~LinkedList(){ clear(); }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept: head_(other.head_), size_(other.size_) {
        other.head_ = nullptr; other.size_ = 0;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_; size_ = other.size_;
            other.head_ = nullptr; other.size_ = 0;
        }
        return *this;
    }

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    void push_front(const T& v){ head_ = new Node(v, head_); ++size_; }
    void push_front(T&& v){ head_ = new Node(std::move(v), head_); ++size_; }

    T& front(){
        if(!head_) throw std::runtime_error("front on empty LinkedList");
        return head_->value;
    }
    const T& front() const{
        if(!head_) throw std::runtime_error("front on empty LinkedList");
        return head_->value;
    }

    T pop_front(){
        if(!head_) throw std::runtime_error("pop_front on empty LinkedList");
        Node* n = head_;
        head_ = n->next;
        T v = std::move(n->value);
        delete n;
        --size_;
        return v;
    }

    void clear(){
        Node* n = head_;
        while(n){ Node* nx = n->next; delete n; n = nx; }
        head_ = nullptr; size_ = 0;
    }

    // Iterador forward muy simple
    class Iterator {
        Node* cur_;
    public:
        explicit Iterator(Node* n): cur_(n) {}
        bool operator!=(const Iterator& other) const { return cur_ != other.cur_; }
        Iterator& operator++() { if (cur_) cur_ = cur_->next; return *this; }
        T& operator*() const { return cur_->value; }
    };

    Iterator begin(){ return Iterator(head_); }
    Iterator end(){ return Iterator(nullptr); }
};
