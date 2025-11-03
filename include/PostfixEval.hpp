#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Token.hpp"

class PostfixEval {
public:
    // Evalúa RPN. Si se pasan símbolos, permite variables (Paso 7 las usaremos).
    // Lanza std::runtime_error ante errores (div. por cero, pila vacía, etc.)
    static double eval(const std::vector<Token>& rpn,
                       const std::unordered_map<std::string,double>* symbols = nullptr);
};
