#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
Lexer::Lexer(std::istream& input) : input(input) {
}


void Lexer::readTokens() {
    double nextLine = 1;
    double nextCol = 1;
    while (!input.eof()) {
        Token token;
        token.line = nextLine;
        token.column = nextCol;
        char currentChar = input.get();
        if (input.eof()) {
            break;
        }
        
        if (currentChar == '(') {
            token.type = Token::TokenType::LEFT_PAREN;
            token.text = "(";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == ')') {
            token.type = Token::TokenType::RIGHT_PAREN;
            token.text = ")";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == '+') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "+";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == '-') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "-";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == '*') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "*";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == '/') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "/";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
            tokens.push_back(token);
        } else if (currentChar == '.') {
            std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
            exit(1);
        } else if (std::isdigit(currentChar)) {
            token.type = Token::TokenType::NUMBER;
            token.line = nextLine;
            token.column = nextCol;
            token.text = currentChar;
            nextCol++;
            bool hasDecimalPoint = false;
            
            while (!input.eof()) {
                char next = input.peek();
                if (std::isdigit(next)) {
                    currentChar = input.get();
                    token.text += currentChar;
                    nextCol++;
                } else if (next == '.') {
                    currentChar = input.get();
                    // Check if there was already a decimal point
                    if (hasDecimalPoint) {
                        std::cerr << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
                        exit(1);
                    }
                    // Check if the decimal is at end of number
                    if (!std::isdigit(input.peek())) {
                        std::cerr << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
                        exit(1);
                    }
                    token.text += currentChar;
                    nextCol++;
                    hasDecimalPoint = true;
                } else {
                    break;
                }
            }
            // Store numbers as doubles
            token.value = std::stod(token.text);
            tokens.push_back(token);
        } else if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
        } else if (currentChar == ' ') {
            nextCol++;
        }
        else {
            // Invalid character
            std::cerr << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
            exit(1);
        }
    }
    // Add END token
    Token end;
    end.line = nextLine;
    end.column = nextCol;
    end.type = Token::TokenType::END;
    end.text = "END";
    tokens.push_back(end);
}


void Lexer::printTokens() {
    
    for (Token t : tokens) {
    std::cout << std::right << std::setw(4) << t.line << std::setw(5)  << t.column << "  " << std::left << t.text << std::endl;
    }
}
