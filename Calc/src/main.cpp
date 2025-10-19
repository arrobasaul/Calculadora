#include <iostream>
#include <unordered_map>
#include <algorithm> // Para std::remove_if
#include <string>    // Para std::string
#include <cctype>    // Para std::isspace
#include <regex>
#include "Token.hpp"
#include "Parser.hpp"
int main(){

    std::string line;
    std::deque<Token> tokens;
    std::queue<Token> outputQueue;
    double result;
    std::unordered_map<std::string, Token> Vars;
    Token pi{};
    pi.type = Token::Type::Number;
    pi.precedence = -1;
    pi.elementStr = "3.14159265358979323846";
    
    Parser parser;
    Vars["pi"] =  pi;
    std::cout << "Varaiables internas:" << std::endl;
    for (const auto& pair : Vars) {
        std::cout << pair.first << ": " << pair.second.elementStr << std::endl;
    }
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        // line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); // quita todos los espacios
        std::regex pattern("\\s+"); // quita dobles espacios
        line = std::regex_replace(line, pattern, " ");
        tokens = parser.GetTokens(line);
        outputQueue = parser.ShuntingYard(tokens);
        result = parser.CalculateResult(outputQueue, Vars);
        std::cout << "" << result << std::endl;
    }

    /*while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        stringLineV.push_back(line);
    }
    std::vector<std::string>::iterator it;
    for (it = stringLineV.begin(); it != stringLineV.end(); it++) {
        tokens = GetTokens(*it);
        outputQueue = ShuntingYard(tokens);
        result = CalculateResult(outputQueue)
        std::cout << "" << result << std::endl;
    }*/
/*
    cparse::TokenMap vars;
    vars["pi"] = 3.14;
    std::cout << cparse::calculator::calculate("pi+1", &vars) << std::endl;

    // Or if you want to evaluate an expression
    // several times efficiently:
    cparse::calculator c1("pi-b");
    vars["b"] = 0.14;
    std::cout << c1.eval(vars) << std::endl; // 3
    vars["b"] = 2.14;
    std::cout << c1.eval(vars) << std::endl; // 1
*/

    return 0;
}