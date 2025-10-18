#pragma once
#include "Token.hpp"
#include <unordered_map>
#include <queue>
#include <string>

class Parser
{
private:
    bool isRetorno = false; 
    std::string variableActual = "";
    std::unordered_map<std::string, Token> Memoria;
public:
public:
    Parser(){}
    ~Parser(){}
    std::deque<Token> GetTokens(std::string expressionLine);
    std::queue<Token> ShuntingYard(std::deque<Token> tokenStack);
    double CalculateResult(std::queue<Token> outputQueue, std::unordered_map<std::string, Token> Vars);
};


