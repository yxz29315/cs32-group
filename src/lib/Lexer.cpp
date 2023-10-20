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
            token.type = Token::TokenType::END;
            token.text = "END";
            token.line = nextLine + 1;
            token.column = 1;
            tokens.push_back(token);
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
                    token.text += currentChar;
                    // Check if there was already a decimal point
                    if (hasDecimalPoint) {
                        std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
                        exit(1);
                    }
                    hasDecimalPoint = true;
                    
                    // Check if the decimal is at end of number
                    if (input.eof() || !std::isdigit(input.peek())) {
                        std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
                        exit(1);
                    }
                    else {
                        while (!input.eof()) {
                            if (std::isdigit(input.peek())) {
                                currentChar = input.get();
                                token.text += currentChar;
                                nextCol++;
                            }
                            else {
                                break;
                            }
                        }
                    }
                    break;
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
        } else {
            std::cerr << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
            exit(1);
        }
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
