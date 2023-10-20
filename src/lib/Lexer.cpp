#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
Lexer::Lexer(std::istream& input) : input(input) {
}

Token Lexer::readTokens() {
    Token token;
    char currentChar;
    double nextLine = 1;
    double nextCol = 1;

    // Initialize line and column numbers
    token.line = nextLine;
    token.column = nextCol;

    while (true) {
        currentChar = input.get();

        if (input.eof()) {
            token.type = Token::TokenType::END;
            token.text = "END";
            token.line = nextLine + 1;
            token.column = 1;
        } else if (currentChar == '(') {
            token.type = Token::TokenType::LEFT_PAREN;
            token.text = "(";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (currentChar == ')') {
            token.type = Token::TokenType::RIGHT_PAREN;
            token.text = ")";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (currentChar == '+') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "+";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (currentChar == '-') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "-";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (currentChar == '*') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "*";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (currentChar == '/') {
            token.type = Token::TokenType::OPERATOR;
            token.text = "/";
            token.line = nextLine;
            token.column = nextCol;
            nextCol++;
        } else if (std::isdigit(currentChar)) {
            token.type = Token::TokenType::NUMBER;
            token.line = nextLine;
            token.column = nextCol;
            token.text = currentChar;
            nextCol++;
            bool hasDecimalPoint = false;
                
            while (!input.eof()) {
                currentChar = input.peek();
                if (std::isdigit(currentChar)) {
                    token.text += currentChar;
                    input.get();
                    nextCol++;
                } else if (currentChar == '.') {
                    input.get();
                    // Check if there was already a decimal point
                    if (hasDecimalPoint) {
                        std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
                        exit(1);
                    }
                    // Check if the decimal is at end of number
                    if (input.eof() || !std::isdigit(input.peek())) {
                        std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
                        exit(1);
                    }
                    token.text += currentChar;
                    input.get();
                    nextCol++;
                } else {
                    break;
                }
            }
            // Store numbers as doubles
            token.value = std::stod(token.text);

        } else if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
        } else if (currentChar == ' ') {
            nextCol++;
        } else {
            std::cerr << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
            exit(1);
        }
        tokens.push_back(token);
    }
}


void Lexer::printTokens() {
    
    for (Token t : tokens) {
        std::cout << "\t" << t.line << "\t" << t.column << "\t" << t.text << std::endl;
    }
    
    /*while ((token = getNextToken()).type != Token::TokenType::END) {
        std::cout << "    " << token.line << "    " << token.column << "  " << token.text << std::endl;
    }
    
    for(const Token& token: tokens) {         
        std::cout << std::setw(4) << token.line << std::setw(4) << token.column << std::setw(2) << token.text << std::endl;
    }*/
}
