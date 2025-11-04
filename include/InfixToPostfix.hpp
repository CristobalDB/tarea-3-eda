#pragma once
#include <vector>
#include "Token.hpp"

class InfixToPostfix {
public:
    
    static std::vector<Token> convert(const std::vector<Token>& infix);
private:
    static int precedence(TokenType t);
    static bool is_left_assoc(TokenType t);
    static bool is_operator(TokenType t);
    static bool is_function(TokenType t);

    static bool is_unary_minus_context(TokenType prev);

    static void pop_while_opstack_has_higher_or_equal(std::vector<Token>& out,
                                                      std::vector<Token>& opstack,
                                                      TokenType current);
};
