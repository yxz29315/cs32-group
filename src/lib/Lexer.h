#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>
#include <istream>

class Lexer {
public:
    Lexer(std::istream& input);
    std::vector<Token> tokenize();
    bool hasSyntaxError() const;
    void printTokensAndPositions() const;

private:
    std::istream& input;
    std::vector<Token> tokens;
    bool syntaxError;

    void readNextToken();
    void skipWhitespace();
    void reportSyntaxError(const std::string& message);
};

#endif // LEX_H

