#pragma once
#include <string>
class Token {
public:
    enum class Type {
        Unknown, 
        Number, 
        LeftP, 
        RightP, 
        Operator,
        Caracter,
        Variable
    };
    Type type;
    int precedence;
    std::string elementStr;
    Token() {}
};