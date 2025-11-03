#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stdexcept>

#include "Tokenizer.hpp"
#include "InfixToPostfix.hpp"
#include "PostfixEval.hpp"
#include "ExprTree.hpp"

// utils simples
static inline std::string ltrim(std::string s){
    std::size_t i=0; while(i<s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    return s.substr(i);
}
static inline std::string rtrim(std::string s){
    if (s.empty()) return s;
    std::size_t i=s.size(); while(i>0 && std::isspace(static_cast<unsigned char>(s[i-1]))) --i;
    return s.substr(0,i);
}
static inline std::string trim(std::string s){ return rtrim(ltrim(std::move(s))); }

static bool is_ident_start(char c){
    return std::isalpha(static_cast<unsigned char>(c)) || c=='_';
}
static bool is_ident_char(char c){
    return std::isalnum(static_cast<unsigned char>(c)) || c=='_';
}
static bool is_valid_ident(const std::string& s){
    if (s.empty()) return false;
    if (!is_ident_start(s[0])) return false;
    for (char c: s) if (!is_ident_char(c)) return false;
    return true;
}

// busca el primer '=' que NO esté dentro de paréntesis
static int find_assign_outside_parens(const std::string& line){
    int depth = 0;
    for (int i=0; i<(int)line.size(); ++i){
        char c = line[i];
        if (c == '(') ++depth;
        else if (c == ')') --depth;
        else if (c == '=' && depth==0) return i;
    }
    return -1;
}

int main() {
    std::cout << "Calculadora EDA — REPL (C++11)\n";
    std::cout << "Comandos: prefix | posfix | tree | show <var> | exit\n";

    std::unordered_map<std::string,double> symbols;
    symbols["ans"] = 0.0;

    std::vector<Token> last_rpn;
    ExprTree last_tree;

    std::string line;
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;

        try {
            // show <id>
            if (line.rfind("show", 0) == 0) {
                std::string rest = trim(line.substr(4));
                if (rest.empty()) { std::cout << "Uso: show <variable>\n"; continue; }
                if (!is_valid_ident(rest)) { std::cout << "Variable inválida: " << rest << "\n"; continue; }
                auto it = symbols.find(rest);
                if (it == symbols.end()) { std::cout << rest << " no definida\n"; }
                else { std::cout << rest << " -> " << it->second << "\n"; }
                continue;
            }

            // posfix / prefix / tree
            if (line == "posfix"){
                if (last_rpn.empty()) { std::cout << "(sin expresión previa)\n"; continue; }
                for (auto& t : last_rpn){
                    if (!t.lexeme.empty()) std::cout << t.lexeme << ' ';
                    else if (t.type == TokenType::Neg) std::cout << "NEG ";
                }
                std::cout << "\n";
                continue;
            }
            if (line == "prefix"){
                if (last_tree.empty()) { std::cout << "(sin expresión previa)\n"; continue; }
                last_tree.print_prefix(std::cout);
                continue;
            }
            if (line == "tree"){
                if (last_tree.empty()) { std::cout << "(sin expresión previa)\n"; continue; }
                last_tree.print_ascii(std::cout);
                continue;
            }

            // ¿Asignación?
            int eq = find_assign_outside_parens(line);
            if (eq >= 0){
                std::string lhs = trim(line.substr(0, eq));
                std::string rhs = trim(line.substr(eq+1));
                if (!is_valid_ident(lhs))
                    throw std::runtime_error("Lado izquierdo de asignación no es un identificador válido");
                if (rhs.empty())
                    throw std::runtime_error("Asignación con RHS vacío");

                auto toks = Tokenizer::tokenize(rhs);
                last_rpn  = InfixToPostfix::convert(toks);
                last_tree = ExprTree::from_postfix(last_rpn);
                double v  = PostfixEval::eval(last_rpn, &symbols);
                symbols[lhs] = v;
                symbols["ans"] = v; // también actualizamos ans
                std::cout << lhs << " -> " << v << "\n";
                continue;
            }

            // Expresión normal
            auto toks = Tokenizer::tokenize(line);
            last_rpn  = InfixToPostfix::convert(toks);
            last_tree = ExprTree::from_postfix(last_rpn);
            double v  = PostfixEval::eval(last_rpn, &symbols);
            symbols["ans"] = v;
            std::cout << "ans -> " << v << "\n";

        } catch (const std::exception& e){
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
