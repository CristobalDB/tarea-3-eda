#pragma once
#include <string>

enum class TokenType {
    Number,       // 12, 3.14
    Identifier,   // x, ans
    Plus, Minus, Mul, Div, Pow,
    LParen, RParen,
    Comma,
    Sqrt,         // sqrt(...)
    Neg,          // menos unario (−x) -> NEG
    End
};

struct Token {
    TokenType type;
    std::string lexeme;  // texto crudo (útil para depurar o mostrar)
    Token(TokenType t = TokenType::End, std::string s = {})
        : type(t), lexeme(std::move(s)) {}
};
