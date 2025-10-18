#include "Parser.hpp"
#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>
#include <cmath>
std::string IsNumber(std::string expressionLine, int* contador)
{
  std::string numero(1, expressionLine[*contador]);
  *contador = *contador + 1;
  if(std::isdigit(expressionLine[*contador]) || expressionLine[*contador] == '.' )
  {
    std::string newNumero = IsNumber(expressionLine, contador);
    numero.append(newNumero);
  }
  return numero;
}
std::string IsLetra(std::string expressionLine, int* contador)
{
  std::string letras(1, expressionLine[*contador]);
  *contador = *contador + 1;
  if(std::isalpha(expressionLine[*contador]) || expressionLine[*contador] == '_' || std::isdigit(expressionLine[*contador]) )
  {
    std::string newLetra = IsLetra(expressionLine, contador);
    letras.append(newLetra);
  }
  return letras;
}
std::deque<Token> Parser::GetTokens(std::string expressionLine) {
  double doubleNr;
  std::string inputElement;
  Token token;
  std::deque<Token> tokenStack;

  std::istringstream iss(expressionLine);

  int tamanioTotal = (int)expressionLine.length();
  int caracterActual = 0;
  
  while(caracterActual < tamanioTotal)
  {
    char actual = expressionLine[caracterActual];
    switch (actual)
    {
    case '(':
      token.elementStr = actual;
      token.type = Token::Type::LeftP;
      token.precedence = -1;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '-':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 2;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '+':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 2;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '*':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 3;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '/':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 3;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '%':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 3;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '^':
      token.elementStr = actual;
      token.type = Token::Type::Operator;
      token.precedence = 3;
      caracterActual++;
      tokenStack.push_back(token);
      break;
    case '=':
      caracterActual++;
      break;
    case ')':
      token.elementStr = actual;
      token.type = Token::Type::RightP;
      token.precedence = -1;
      caracterActual++;
      if (caracterActual < tamanioTotal)
      {
        if (expressionLine[caracterActual] == '(')
        {
          tokenStack.push_back(token);
          token.elementStr = "*";
          token.type = Token::Type::Operator;
          token.precedence = 3;
        }
      }
      tokenStack.push_back(token);
      break;
    default:
      if(std::isdigit(actual))
      {
        std::string numero = IsNumber(expressionLine, &caracterActual);
        token.elementStr = numero;
        token.precedence = -1;
        token.type = Token::Type::Number;
        tokenStack.push_back(token);
      }else if(std::isalpha(actual) || actual == '_' ){
        int tempCaracterActual = caracterActual;
        
        std::string letras = IsLetra(expressionLine, &caracterActual);
        if (caracterActual < tamanioTotal)
        {
            if (expressionLine[caracterActual] == ' ')
            {
                caracterActual++;
            }
            if (expressionLine[caracterActual] == '=')
            {
                if (tempCaracterActual == 0) //
                {
                    isRetorno = true;
                    variableActual = letras;
                    token.elementStr = letras;
                    token.precedence = -1;
                    token.type = Token::Type::Unknown; 
                    Memoria.insert({letras, token});
                    caracterActual++;
                }
                else{
                    token.elementStr = letras;
                    token.precedence = -1;
                    token.type = Token::Type::Caracter; 
                    tokenStack.push_back(token);
                }
            }
            else{
                token.elementStr = letras;
                token.precedence = -1;
                token.type = Token::Type::Caracter; 
                tokenStack.push_back(token);
            }
        }
        else{
            token.elementStr = letras;
            token.precedence = -1;
            token.type = Token::Type::Caracter; 
            tokenStack.push_back(token);
        }
      }
      else if(expressionLine[caracterActual] == ' '){
        caracterActual++;
      }
      break;
    }
  }
  return tokenStack;
}

std::string FixPrecision(std::string x) {
  std::ostringstream strout ;
  std::string str;

  double doubleNr = std::stod(x);
  strout << std::setprecision(10) << doubleNr;
  str = strout.str() ;
  size_t end = str.find_last_not_of( '.' ) + 1;
  str.erase(end);
  return str;
}
std::queue<Token> Parser::ShuntingYard(std::deque<Token> tokenStack) {
  Token token;
  std::queue<Token> outputQueue;
  std::stack<Token> operatorStack;

  while(!tokenStack.empty()) {
    token = tokenStack.front();
    tokenStack.pop_front();
    if (token.type == Token::Type::Number) {
      token.elementStr = FixPrecision(token.elementStr);
      outputQueue.push(token);
    }
    else if (token.type == Token::Type::Caracter) {
      outputQueue.push(token);
    }
    else if (token.type == Token::Type::Variable) {
      outputQueue.push(token);
    }
    else if (token.type == Token::Type::Operator) {
      Token o1 = token;
      while (!operatorStack.empty()) {
        Token o2 = operatorStack.top();
        if (o2.type != Token::Type::LeftP && (o1.precedence <= o2.precedence)) {
          operatorStack.pop();
          outputQueue.push(o2);
        }
        else break;
      }
      operatorStack.push(o1);
    }
    else if (token.type == Token::Type::LeftP) {
      operatorStack.push(token);
    }
    else if (token.type == Token::Type::RightP) {
      while(!operatorStack.empty() && operatorStack.top().type != Token::Type::LeftP) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
      if (operatorStack.top().type == Token::Type::LeftP) {
        operatorStack.pop();
      }
    }
    else break;
  }
  while(!operatorStack.empty()) {
    if (operatorStack.top().type != Token::Type::LeftP) {
      outputQueue.push(operatorStack.top());
      operatorStack.pop();
    }
    else break;
  }
  return outputQueue;
}
double Parser::CalculateResult(std::queue<Token> outputQueue, std::unordered_map<std::string, Token> Vars) {
  std::vector<double> operandsV;

  while(!outputQueue.empty()) {
    Token token = outputQueue.front();
    outputQueue.pop();
    if (token.type == Token::Type::Number) {
    operandsV.push_back(std::stod(token.elementStr));
    }
    else if (token.type == Token::Type::Caracter) {
        auto valorEncontrado = Vars.find(token.elementStr);
        auto valorEncontradoMemoria = Memoria.find(token.elementStr);
        if (valorEncontrado != Vars.end()) {
            Token valor = valorEncontrado->second;
            if(valor.type == Token::Type::Number){
                operandsV.push_back(std::stod(valor.elementStr));
            }
            else{
                operandsV.push_back(0.0);
            }
        } else if (valorEncontradoMemoria != Memoria.end()) {
            Token valor = valorEncontradoMemoria->second;
            if(valor.type == Token::Type::Number){
                operandsV.push_back(std::stod(valor.elementStr));
            }
            else{
                operandsV.push_back(0.0);
            }
        } else {
            operandsV.push_back(0.0);
        }
    }
    if (token.type == Token::Type::Operator) {
        double operandR = operandsV.back();
        operandsV.pop_back();
        double operandL = operandsV.back();
        operandsV.pop_back();
        if (token.elementStr == "*") {
            operandsV.push_back(operandL * operandR);
        }
        if (token.elementStr == "/") {
            operandsV.push_back(operandL / operandR);
        }
        if (token.elementStr == "%") {
            operandsV.push_back((double) ((int) operandL % (int) operandR));
        }
        if (token.elementStr == "+") {
            operandsV.push_back(operandL + operandR);
        }
        if (token.elementStr == "-") {
            operandsV.push_back(operandL - operandR);
        }
        if (token.elementStr == "^") {
            operandsV.push_back(std::pow(operandL, operandR));
        }
    }
  }
  if (isRetorno)
  {
    if (variableActual != "")
    {
        Token token;
        token.elementStr = std::to_string(operandsV[0]);
        token.precedence = -1;
        token.type = Token::Type::Number; 
        Memoria[variableActual] = token;
        variableActual = "";
    }
  }
 return operandsV[0];
}