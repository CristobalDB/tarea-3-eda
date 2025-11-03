#include <iostream>
#include <cassert>
#include "LinkedList.hpp"
#include "Stack.hpp"

static void test_linked_list(){
    LinkedList<int> L;
    assert(L.empty());
    L.push_front(3);
    L.push_front(2);
    L.push_front(1);
    assert(L.size() == 3);
    assert(L.front() == 1);
    int a = L.pop_front(); // 1
    int b = L.pop_front(); // 2
    int c = L.pop_front(); // 3
    assert(a==1 && b==2 && c==3);
    assert(L.empty());
}

static void test_stack(){
    Stack<std::string> S;
    S.push("a"); S.push("b"); S.push("c");
    assert(S.size()==3);
    assert(S.top()=="c");
    auto x = S.pop(); // c
    auto y = S.pop(); // b
    auto z = S.pop(); // a
    assert(x=="c" && y=="b" && z=="a");
    assert(S.empty());
}

int main(){
    test_linked_list();
    test_stack();
    std::cout << "[OK] Paso 2: TADs LinkedList y Stack\n";
    return 0;
}
