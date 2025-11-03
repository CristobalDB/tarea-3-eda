#include "lLists/node.hpp"
#include "lLists/queue.hpp"
#include "lLists/stack.hpp"
#include <iostream>
#include <string>

using namespace eda;

bool validateParenthesis(const std::string &input){
    bool error = false;
    int i = 0;
    Stack stack;
    while (!error && i < static_cast<int>(input.length())){
        if (input[i] == '(') {
            stack.push(new Node(input[i]));
        }
        if (input[i] == ')') {
            if (stack.isEmpty()){
                error = true;
            } else {
                stack.pop();
            }
        }
        i = i + 1;
    }
    if (!stack.isEmpty()){
        error = true;
    }
    return !error;
}

int main(){
    std::string input;
    std::cout << "Ingresa expresión: ";
    std::cin >> input;
    bool status = validateParenthesis(input);
    if (status) std::cout << "Expresión Correcta\n";
    else        std::cout << "Expresión Inválida\n";
    return 0;
}
