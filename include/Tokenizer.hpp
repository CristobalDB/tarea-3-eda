#pragma once
#include <vector>
#include <string>
#include "Token.hpp"

class Tokenizer {
public:
    // Tokeniza una línea y además inserta '*' implícitos donde corresponda (p.ej. 2(3+4), x(1+y), )(
    static std::vector<Token> tokenize(const std::string& line);

private:
    static void push_implicit_mul_if_needed(std::vector<Token>& out, TokenType nextStart);
    static bool is_ident_start(char c);
    static bool is_ident_char(char c);
};
