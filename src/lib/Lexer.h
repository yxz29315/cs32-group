// lexer.h
#pragma once

#include <string>
#include <vector>

struct Token {
    std::string text;
    int line;
    int column;
    double value;
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
    void printTokens();

private:
    std::istream& input;
    std::vector<Token> tokens;
    Token getNextToken();
    void skipWhitespace();
};

