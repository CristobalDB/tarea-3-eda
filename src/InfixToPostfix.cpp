#include "InfixToPostfix.hpp"
#include <stdexcept>

static bool is_open_paren(TokenType t){ return t == TokenType::LParen; }
static bool is_close_paren(TokenType t){ return t == TokenType::RParen; }

int InfixToPostfix::precedence(TokenType t){
    switch(t){
        case TokenType::Neg:                  return 4; // unario: más alto que ^
        case TokenType::Pow:                  return 3; // ^ (right-assoc)
        case TokenType::Mul:
        case TokenType::Div:                  return 2;
        case TokenType::Plus:
        case TokenType::Minus:                return 1;
        default:                              return 0;
    }
}

bool InfixToPostfix::is_left_assoc(TokenType t){
    // ^ y NEG son right-assoc; el resto left-assoc
    return !(t == TokenType::Pow || t == TokenType::Neg);
}

bool InfixToPostfix::is_operator(TokenType t){
    switch(t){
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Mul:
        case TokenType::Div:
        case TokenType::Pow:
        case TokenType::Neg:
            return true;
        default:
            return false;
    }
}

bool InfixToPostfix::is_function(TokenType t){
    return (t == TokenType::Sqrt);
}

bool InfixToPostfix::is_unary_minus_context(TokenType prev){
    // Al inicio (End), o tras operador, o tras '(' o ',' => '-' es unario
    if (prev == TokenType::End) return true;
    if (is_operator(prev)) return true;
    if (prev == TokenType::LParen) return true;
    if (prev == TokenType::Comma) return true;
    return false;
}

void InfixToPostfix::pop_while_opstack_has_higher_or_equal(std::vector<Token>& out,
                                                           std::vector<Token>& opstack,
                                                           TokenType current)
{
    while(!opstack.empty()){
        TokenType top = opstack.back().type;
        if (!is_operator(top)) break;

        int pc = precedence(current);
        int pt = precedence(top);

        if ( (is_left_assoc(current)  && pt >= pc) ||
             (!is_left_assoc(current) && pt >  pc) )
        {
            out.push_back(opstack.back());
            opstack.pop_back();
        } else {
            break;
        }
    }
}

std::vector<Token> InfixToPostfix::convert(const std::vector<Token>& infix){
    std::vector<Token> out;
    std::vector<Token> opstack;

    TokenType prev = TokenType::End; // contexto para menos unario

    for (std::size_t i=0; i<infix.size(); ++i){
        Token tk = infix[i];

        switch(tk.type){
            case TokenType::Number:
            case TokenType::Identifier:
                out.push_back(tk);
                prev = tk.type;
                break;

            case TokenType::Sqrt:
                // función: apilar y esperar '(' y su argumento
                opstack.push_back(tk);
                prev = tk.type;
                break;

            case TokenType::Comma:
                // sacar hasta el '(' más cercano
                while(!opstack.empty() && !is_open_paren(opstack.back().type)){
                    out.push_back(opstack.back());
                    opstack.pop_back();
                }
                if (opstack.empty())
                    throw std::runtime_error("Coma fuera de función / paréntesis");
                prev = tk.type;
                break;

            case TokenType::LParen:
                opstack.push_back(tk);
                prev = tk.type;
                break;

            case TokenType::RParen:
                // pop hasta encontrar '('
                while(!opstack.empty() && !is_open_paren(opstack.back().type)){
                    out.push_back(opstack.back());
                    opstack.pop_back();
                }
                if (opstack.empty())
                    throw std::runtime_error("Paréntesis desbalanceados");
                // quitar '('
                opstack.pop_back();
                // si al tope hay una función, también enviarla a salida
                if(!opstack.empty() && is_function(opstack.back().type)){
                    out.push_back(opstack.back());
                    opstack.pop_back();
                }
                prev = tk.type;
                break;

            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Mul:
            case TokenType::Div:
            case TokenType::Pow: {
                // detectar menos unario
                TokenType cur = tk.type;
                if (cur == TokenType::Minus && is_unary_minus_context(prev)){
                    cur = TokenType::Neg; // convertir a NEG
                    tk = Token(cur, "NEG");
                }
                // pop según precedencia/aso
                pop_while_opstack_has_higher_or_equal(out, opstack, cur);
                opstack.push_back(tk);
                prev = cur;
                break;
            }

            case TokenType::End:
                // ignorar
                break;
        }
    }

    // vaciar pila de operadores
    while(!opstack.empty()){
        if (is_open_paren(opstack.back().type) || is_close_paren(opstack.back().type))
            throw std::runtime_error("Paréntesis desbalanceados");
        out.push_back(opstack.back());
        opstack.pop_back();
    }
    return out;
}
