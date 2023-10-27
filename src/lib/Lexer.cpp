
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
    while (input) {
        Token token;
        token.line = nextLine;
        token.column = nextCol;
        char currentChar = input.get();
        if (input.eof()) {
            break;
        }
        //std::cout << "currentChar: '" << currentChar << "'\tASCI: '" << static_cast<int>(currentChar) << "'\n";
        if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
            //std::cout << "currentChar == newline\n";
        } else if (currentChar == ' ') {
            nextCol++;
            //std::cout << "currentChar == space\n";
        } else if (currentChar == '\t') {
            //std::cout << "tab detected" << std::endl;
            nextCol++;
            //std::cout << "currentChar == tab/space\n";
        }
        else if (currentChar == '(') {
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
            std::cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
            exit(1);
        } else if (std::isdigit(currentChar)) {
            token.type = Token::TokenType::NUMBER;
            token.line = nextLine;
            token.column = nextCol;
            token.text = currentChar;
            nextCol++;
            bool hasDecimalPoint = false;
            
            while (!input.eof() && input.peek() != EOF) {
                char next = input.peek();
                if (std::isdigit(next)) {
                    currentChar = input.get();
                    token.text += currentChar;
                    nextCol++;
                } else if (next == '.') {
                    currentChar = input.get();
                    // Check if there was already a decimal point
                    if (hasDecimalPoint) {
                        std::cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
                        exit(1);
                    }
                    // Check if the decimal is at end of number
                    if (!std::isdigit(input.peek())) {
                        nextCol++;
                        std::cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
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
        } 
        else {
            // Invalid character
            nextLine++;
            nextCol++;

            std::cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
            exit(1);
        }
    }
    // Add END token
    Token end;
    end.line = nextLine;//nextLine;
    end.column = nextCol;//nextCol;
    end.type = Token::TokenType::END;
    end.text = "END";
    tokens.push_back(end);
}


void Lexer::printTokens() {
    
    for (Token t : tokens) {
        std::cout << std::setfill(' ') << std::setw(4)  << std::right << t.line << std::setfill(' ') << std::setw(5)  << std::right << t.column << "  " << std::left << t.text << std::endl;
    }
}

std::queue<Token> Lexer::returnTokens() {
    return tokens;
}