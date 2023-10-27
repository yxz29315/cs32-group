#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <queue>
#include <set>

struct Token {
    std::string text;
    int line;
    int column;
    enum class TokenType {
        LEFT_PAREN,
        RIGHT_PAREN,
        OPERATOR,
        NUMBER,
        END
    } type;
};

class Lexer {
public:
    Lexer(std::istream& input);
    void readTokens();
    void printTokens();
    std::queue<Token> returnTokens();

private:
    std::istream& input;
    std::queue<Token> tokens;
};

