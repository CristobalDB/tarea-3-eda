#include "Tokenizer.hpp"
#include "InfixToPostfix.hpp"
#include <iostream>
#include <iomanip>

static const char* tt(TokenType t){
    switch(t){
        case TokenType::Number: return "Number";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Mul: return "Mul";
        case TokenType::Div: return "Div";
        case TokenType::Pow: return "Pow";
        case TokenType::LParen: return "LParen";
        case TokenType::RParen: return "RParen";
        case TokenType::Comma: return "Comma";
        case TokenType::Sqrt: return "Sqrt";
        case TokenType::Neg: return "Neg";
        case TokenType::End: return "End";
    }
    return "?";
}

int main(){
    std::string s;
    std::cout << "Expr: ";
    std::getline(std::cin, s);

    auto toks = Tokenizer::tokenize(s);
    auto rpn  = InfixToPostfix::convert(toks);

    std::cout << "\nPostfix tokens:\n";
    for (auto& t : rpn){
        std::cout << std::left << std::setw(10) << tt(t.type)
                  << "  '" << t.lexeme << "'\n";
    }

    std::cout << "\nPostfix (lexemes): ";
    for (auto& t : rpn){
        if (!t.lexeme.empty()) std::cout << t.lexeme << ' ';
        else {
            // imprime símbolo estándar para operadores sin lexema
            switch(t.type){
                case TokenType::Neg: std::cout << "NEG "; break;
                default: break;
            }
        }
    }
    std::cout << "\n";
    return 0;
}
