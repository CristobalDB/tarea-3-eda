#pragma once
#include <string>

enum class TokenType {
    Number,
    Identifier,
    Plus, Minus, Mul, Div, Pow,
    LParen, RParen,
    Comma,
    Sqrt,
    Neg,
    End
};

struct Token {
    TokenType type;
    std::string lexeme;
    Token(TokenType t = TokenType::End, std::string s = {})
        : type(t), lexeme(std::move(s)) {}
};
