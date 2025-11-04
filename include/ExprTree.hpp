#pragma once
#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include "Token.hpp"

struct ExprNode {
    Token tok;
    std::shared_ptr<ExprNode> left;
    std::shared_ptr<ExprNode> right;
    explicit ExprNode(const Token& t) : tok(t), left(nullptr), right(nullptr) {}
};

class ExprTree {
public:
    ExprTree() = default;
    explicit ExprTree(std::shared_ptr<ExprNode> r) : root_(std::move(r)) {}

    const std::shared_ptr<ExprNode>& root() const { return root_; }
    bool empty() const { return !root_; }

    static ExprTree from_postfix(const std::vector<Token>& rpn);

    void print_prefix(std::ostream& os) const;
    void print_postfix(std::ostream& os) const;
    void print_ascii(std::ostream& os) const;

private:
    std::shared_ptr<ExprNode> root_{};

    static void prefix_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n);
    static void postfix_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n);
    static std::string show_lex(const Token& t);
    static void ascii_rec(std::ostream& os, const std::shared_ptr<ExprNode>& n,
                          const std::string& indent, bool isLeft);
};
