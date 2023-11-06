#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <deque>
#include <set>

struct Token {
    std::string text;
    int line;
    int column;
    enum class TokenType {
        OPERATOR,
        NUMBER,
        END,
        IDENTIFIER,
        LEFTP,
        RIGHTP
    } type;
};

class Lexer {
public:
    void readTokens(std::string inputString);
    void printTokens();
    std::deque<Token> getTokens();

private:
    std::deque<Token> tokens;
};

#endif