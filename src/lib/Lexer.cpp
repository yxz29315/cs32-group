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
    char currentChar;
    std::string temp;

    while (input.get(currentChar)) {

        if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
            continue;
        }

        if (!isspace(currentChar)) {
            if (currentChar == '(' || currentChar == ')' || currentChar == '+' ||
                currentChar == '-' || currentChar == '*' || currentChar == '/') {
                    Token x;
                    x.line = nextLine;
                    x.column = nextCol;
                    x.type = Token::TokenType::OPERATOR;
                    x.text = "";
                    x.text += currentChar;
                    tokens.push(x);
            }
            else if (isdigit(currentChar)) {
                bool hasDec = false;
                std::string temp2 = "";
                temp2 += currentChar;
                int col1 = nextCol;

                while ((isdigit(input.peek()) || input.peek() == '.')) {
                    if (input.peek() == '.') {
                        if (hasDec) {
                            std::cout << "Syntax error on line " << nextLine << " column " << nextCol + 1 << ".\n";
                            exit(1);
                        }
                        else {
							hasDec = true;
                        }
                    }
                    char next;
                    input.get(next);
                    temp2 += next;
                    nextCol++;
                }

                if (temp2.back() == '.') {
                    std::cout << "Syntax error on line " << nextLine << " column " << nextCol + 1 << ".\n";
                    exit(1);
                }
                Token y;
                y.line = nextLine;
                y.column = col1;
                y.text = temp2;
                tokens.push(y);
            }
            else {
                std::cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
                exit(1);
            }
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