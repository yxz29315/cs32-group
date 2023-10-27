#ifndef LEXER_H
#define LEXER_H

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
        OPERATOR,
        NUMBER,
        END
    } type;
};

class Lexer {
public:
    void readTokens(std::string inputString);
    void printTokens();
    std::queue<Token> getTokens();

private:
    std::queue<Token> tokens;
};

#endif