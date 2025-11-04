#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Token.hpp"

class PostfixEval {
public:
    static double eval(const std::vector<Token>& rpn,
                       const std::unordered_map<std::string,double>* symbols = nullptr);
};
