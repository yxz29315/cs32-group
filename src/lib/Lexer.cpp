#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>


void Lexer::readTokens(std::string inputStr) {
    std::istringstream stream(inputStr);
    double nextLine = 1;
    double nextCol = 1;
    char currentChar;
    std::string temp;

    while (stream.get(currentChar)) {

        if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
            continue;
        }

        if (!isspace(currentChar)) {
            if (currentChar == '(' || currentChar == ')' || currentChar == '+' ||
                currentChar == '-' || currentChar == '*' || currentChar == '/' ||
                currentChar == '=') {
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

                while ((isdigit(stream.peek()) || stream.peek() == '.')) {
                    if (stream.peek() == '.') {
                        if (hasDec) {
                            std::cout << "Syntax error on line " << nextLine << " column " << nextCol + 1 << ".\n";
                            exit(1);
                        }
                        else {
							hasDec = true;
                        }
                    }
                    char next;
                    stream.get(next);
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
        nextCol++;
    }
    // Add END token
    Token end;
    end.line = nextLine;
    end.column = nextCol;
    end.type = Token::TokenType::END;
    end.text = "END";
    tokens.push(end);
}


void Lexer::printTokens() {
    
    while (!tokens.empty()) {
        Token cur = tokens.front();
        std::cout << std::setfill(' ')  << std::setw(4) << std::right << cur.line << std::setfill(' ')
        << std::setw(5) << std::right << cur.column << "  " << cur.text << std::endl;
        tokens.pop();
    }
}

std::queue<Token> Lexer::getTokens() {
    return tokens;
}
