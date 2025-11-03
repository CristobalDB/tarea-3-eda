#include "PostfixEval.hpp"
#include <stack>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

static double pop_or_throw(std::stack<double>& st, const char* ctx){
    if (st.empty()) throw std::runtime_error(std::string("RPN: pila vacía en ")+ctx);
    double v = st.top(); st.pop(); return v;
}

double PostfixEval::eval(const std::vector<Token>& rpn,
                         const std::unordered_map<std::string,double>* symbols)
{
    std::stack<double> st;

    for (const auto& tk : rpn){
        switch(tk.type){
            case TokenType::Number: {
                // stod lanza si no es convertible
                double v = std::stod(tk.lexeme);
                st.push(v);
                break;
            }
            case TokenType::Identifier: {
                if (!symbols) {
                    throw std::runtime_error("Variable usada sin tabla de símbolos: " + tk.lexeme);
                }
                auto it = symbols->find(tk.lexeme);
                if (it == symbols->end()){
                    throw std::runtime_error("Variable no definida: " + tk.lexeme);
                }
                st.push(it->second);
                break;
            }
            case TokenType::Neg: {
                double a = pop_or_throw(st, "NEG");
                st.push(-a);
                break;
            }
            case TokenType::Sqrt: {
                double a = pop_or_throw(st, "sqrt");
                if (a < 0.0) throw std::runtime_error("sqrt: argumento negativo");
                st.push(std::sqrt(a));
                break;
            }
            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Mul:
            case TokenType::Div:
            case TokenType::Pow: {
                double b = pop_or_throw(st, "binop rhs");
                double a = pop_or_throw(st, "binop lhs");
                double r = 0.0;
                switch(tk.type){
                    case TokenType::Plus:  r = a + b; break;
                    case TokenType::Minus: r = a - b; break;
                    case TokenType::Mul:   r = a * b; break;
                    case TokenType::Div:
                        if (b == 0.0) throw std::runtime_error("División por cero");
                        r = a / b; break;
                    case TokenType::Pow:   r = std::pow(a, b); break;
                    default: break;
                }
                st.push(r);
                break;
            }
            case TokenType::LParen:
            case TokenType::RParen:
            case TokenType::Comma:
            case TokenType::End:
                // no aparecen en RPN bien formada
                break;
        }
    }

    if (st.size() != 1){
        throw std::runtime_error("RPN: expresión inválida (restan elementos en la pila)");
    }
    return st.top();
}
