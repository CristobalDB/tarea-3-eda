#include "Tokenizer.hpp"
#include "InfixToPostfix.hpp"
#include "PostfixEval.hpp"
#include <unordered_map>
#include <iostream>
#include <string>

int main(){
    std::unordered_map<std::string,double> symbols;
    symbols["ans"] = 0.0;

    std::string s;
    std::cout << "Expr: ";
    while (std::getline(std::cin, s)){
        if (s == "exit") break;
        try {
            auto toks = Tokenizer::tokenize(s);
            auto rpn  = InfixToPostfix::convert(toks);
            double v  = PostfixEval::eval(rpn, &symbols);
            symbols["ans"] = v;
            std::cout << "=> " << v << "\n";
        } catch (const std::exception& e){
            std::cout << "Error: " << e.what() << "\n";
        }
        std::cout << "Expr: ";
    }
    return 0;
}
