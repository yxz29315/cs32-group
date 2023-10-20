#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
Lexer::Lexer(std::istream& input) : input(input) {
    
}

Token Lexer::getNextToken() {
    char currentChar;

    Token token;
    token.line = 1; // Initialize line and column numbers here
    token.column = 1;

    while (true) {
        currentChar = input.get();

        if (input.eof()) {
            token.type = Token::TokenType::END;
            token.text = "END";
            return token;
        } else if (currentChar == '(') {
            token.type = Token::TokenType::LEFT_PAREN;
            token.text = "(";
            return token;
        } else if (currentChar == ')') {
            token.type = Token::TokenType::RIGHT_PAREN;
            token.text = ")";
            return token;
        } else if (currentChar == '+') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "+";
            return token;
        } else if (currentChar == '-') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "-";
            return token;
        } else if (currentChar == '*') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "*";
            return token;
        } else if (currentChar == '/') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "/";
            return token;
        } else if (std::isdigit(currentChar) || currentChar == '.') {
            token.type = Token::TokenType::NUMBER;
            token.text = currentChar;

            while (true) {
                currentChar = input.peek();
                if (std::isdigit(currentChar) || currentChar == '.') {
                    token.text += currentChar;
                    input.get();
                } else {
                    break;
                }
            }

            // Store numbers as doubles
            token.value = std::stod(token.text);
            return token;
        } else if (currentChar == '\n') {
            token.line++;      // Advance to the next line
            token.column = 1; // Reset the column number
        } else if (currentChar == ' ') {
            // Skip spaces
        } else {
            std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
            exit(1);
        }
    }
}


void Lexer::printTokens() {
    
    Token token;
    while ((token = getNextToken()).type != Token::TokenType::END) {
        std::cout << "Line: " << token.line << ", Column: " << token.column << ", Token: " << token.text << std::endl;
    }
    
    /*for(const Token& token: tokens) {         
        std::cout << std::setw(4) << token.line << std::setw(4) << token.column << std::setw(2) << token.text << std::endl;
    }*/
}
