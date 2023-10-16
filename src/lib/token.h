#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    LPAREN, // Left parenthesis
    RPAREN, // Right parenthesis
    // Add more token types as needed
};

struct Token {
    TokenType type;
    int line;
    int column;
    string text;
};

Token* create_token(TokenType type, int line, int column, const string& text);
void free_token(Token* token);

#endif