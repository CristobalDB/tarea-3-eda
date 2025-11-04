#include "Tokenizer.hpp"
#include <cctype>

bool Tokenizer::is_ident_start(char c){
    return std::isalpha(static_cast<unsigned char>(c)) || c=='_';
}
bool Tokenizer::is_ident_char(char c){
    return std::isalnum(static_cast<unsigned char>(c)) || c=='_';
}

void Tokenizer::push_implicit_mul_if_needed(std::vector<Token>& out, TokenType nextStart){
    if (out.empty()) return;
    const Token& prev = out.back();

    auto prev_is_atom = (prev.type == TokenType::Number) ||
                        (prev.type == TokenType::Identifier) ||
                        (prev.type == TokenType::RParen);
    auto next_is_atom = (nextStart == TokenType::Number) ||
                        (nextStart == TokenType::Identifier) ||
                        (nextStart == TokenType::LParen) ||
                        (nextStart == TokenType::Sqrt);

    if (prev_is_atom && next_is_atom) {
        out.emplace_back(TokenType::Mul, "*");
    }
}

std::vector<Token> Tokenizer::tokenize(const std::string& line){
    std::vector<Token> out;
    std::size_t i=0, n=line.size();

    while (i<n){
        char c=line[i];
        if (std::isspace(static_cast<unsigned char>(c))){ ++i; continue; }

        if (std::isdigit(static_cast<unsigned char>(c)) || c=='.'){
            push_implicit_mul_if_needed(out, TokenType::Number);
            std::size_t j=i+1;
            while (j<n && (std::isdigit(static_cast<unsigned char>(line[j])) || line[j]=='.')) ++j;
            out.emplace_back(TokenType::Number, line.substr(i, j-i));
            i=j; continue;
        }

        if (is_ident_start(c)){
            std::size_t j=i+1;
            while (j<n && is_ident_char(line[j])) ++j;
            std::string id = line.substr(i, j-i);

            TokenType t = TokenType::Identifier;
            if (id == "sqrt") t = TokenType::Sqrt;

            push_implicit_mul_if_needed(out, t);
            out.emplace_back(t, id);
            i=j; continue;
        }

        switch(c){
            case '+': out.emplace_back(TokenType::Plus, "+"); break;
            case '-': out.emplace_back(TokenType::Minus, "-"); break;
            case '*': out.emplace_back(TokenType::Mul, "*"); break;
            case '/': out.emplace_back(TokenType::Div, "/"); break;
            case '^': out.emplace_back(TokenType::Pow, "^"); break;
            case '(': {
                push_implicit_mul_if_needed(out, TokenType::LParen);
                out.emplace_back(TokenType::LParen, "(");
                break;
            }
            case ')': out.emplace_back(TokenType::RParen, ")"); break;
            case ',': out.emplace_back(TokenType::Comma, ","); break;
            default: break;
        }
        ++i;
    }

    return out;
}
