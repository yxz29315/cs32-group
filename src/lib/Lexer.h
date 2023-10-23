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
    void readTokens();
    void printTokens();
    std::vector<Token> returnTokens();

private:
    std::istream& input;
    std::vector<Token> tokens;
};

