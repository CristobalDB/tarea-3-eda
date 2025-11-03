#include "Tokenizer.hpp"
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
        case TokenType::End: return "End";
    }
    return "?";
}

int main(){
    std::string s;
    std::cout << "Expr: ";
    std::getline(std::cin, s);
    auto toks = Tokenizer::tokenize(s);
    for (auto& t : toks){
        std::cout << std::left << std::setw(10) << tt(t.type)
                  << "  '" << t.lexeme << "'\n";
    }
    return 0;
}
