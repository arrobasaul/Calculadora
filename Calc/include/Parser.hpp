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
    std::string precedentString = "-+*/^%";
    std::unordered_map<char, int> presedents;
    std::unordered_map<std::string, Token> Memoria;
    std::string Last;
public:
public:
    Parser(){
        for (size_t i = 0; i < precedentString.length(); i++)
        {
            presedents.insert({precedentString[i], i});
        }
    }
    ~Parser(){}
    std::deque<Token> GetTokens(std::string expressionLine);
    std::queue<Token> ShuntingYard(std::deque<Token> tokenStack);
    double CalculateResult(std::queue<Token> outputQueue, std::unordered_map<std::string, Token> Vars);
};


