#include "ExprTree.hpp"
#include <vector>
#include <stdexcept>

static bool is_unary(TokenType t){
    return t == TokenType::Neg || t == TokenType::Sqrt;
}
static bool is_binary(TokenType t){
    switch(t){
        case TokenType::Plus: case TokenType::Minus:
        case TokenType::Mul:  case TokenType::Div:
        case TokenType::Pow:
            return true;
        default: return false;
    }
}

ExprTree ExprTree::from_postfix(const std::vector<Token>& rpn){
    std::vector<std::shared_ptr<ExprNode>> st;
    st.reserve(rpn.size());

    for (const auto& tk : rpn){
        if (tk.type == TokenType::Number || tk.type == TokenType::Identifier){
            st.emplace_back(std::make_shared<ExprNode>(tk));
        } else if (is_unary(tk.type)){
            if (st.empty()) throw std::runtime_error("RPN inválida: falta operando unario");
            auto a = st.back(); st.pop_back();
            auto n = std::make_shared<ExprNode>(tk);
            n->left = a;
            st.emplace_back(n);
        } else if (is_binary(tk.type)){
            if (st.size() < 2) throw std::runtime_error("RPN inválida: faltan operandos binarios");
            auto b = st.back(); st.pop_back();
            auto a = st.back(); st.pop_back();
            auto n = std::make_shared<ExprNode>(tk);
            n->left = a;
            n->right = b;
            st.emplace_back(n);
        } else {
        }
    }
    if (st.size() != 1) throw std::runtime_error("RPN inválida: sobran elementos");
    return ExprTree(st.back());
}

std::string ExprTree::show_lex(const Token& t){
    if (!t.lexeme.empty()) return t.lexeme;
    switch(t.type){
        case TokenType::Neg:  return "NEG";
        case TokenType::Plus: return "+";
        case TokenType::Minus:return "-";
        case TokenType::Mul:  return "*";
        case TokenType::Div:  return "/";
        case TokenType::Pow:  return "^";
        case TokenType::Sqrt: return "sqrt";
        default: return "?";
    }
}

void ExprTree::prefix_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n){
    if (!n) return;
    os << show_lex(n->tok) << ' ';
    prefix_rec(os, n->left);
    prefix_rec(os, n->right);
}
void ExprTree::postfix_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n){
    if (!n) return;
    postfix_rec(os, n->left);
    postfix_rec(os, n->right);
    os << show_lex(n->tok) << ' ';
}

void ExprTree::ascii_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n,
                         const std::string& indent, bool isLeft)
{
    if (!n) return;
    os << indent;
    os << (isLeft ? "├─" : "└─");
    os << show_lex(n->tok) << "\n";

    std::string nextIndent = indent + (isLeft ? "│ " : "  ");
    if (n->left || n->right){
        if (n->left)  ascii_rec(os, n->left,  nextIndent, true);
        if (n->right) ascii_rec(os, n->right, nextIndent, false);
    }
}

void ExprTree::print_prefix(std::ostream& os) const {
    if (empty()) { os << "(árbol vacío)\n"; return; }
    prefix_rec(os, root_);
    os << "\n";
}
void ExprTree::print_postfix(std::ostream& os) const {
    if (empty()) { os << "(árbol vacío)\n"; return; }
    postfix_rec(os, root_);
    os << "\n";
}
void ExprTree::print_ascii(std::ostream& os) const {
    if (empty()) { os << "(árbol vacío)\n"; return; }
    os << show_lex(root_->tok) << "\n";
    if (root_->left)  ascii_rec(os, root_->left,  "", true);
    if (root_->right) ascii_rec(os, root_->right, "", false);
}
