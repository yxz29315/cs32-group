#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

// Enum to represent different token types
enum class TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    OPERATOR,
    NUMBER,
    END
};

// Structure to represent a token
struct Token {
    TokenType type;
    double number; // Store numbers as doubles
    double line;   // Use double for line
    double column; // Use double for column
    char opS;
    // Constructor for other token types
    Token(TokenType t, double l, double c, char o = ' ') : type(t), number(0.0), line(l), column(c), opS(o) {}

    // Constructor for NUMBER token
    Token(double num, double l, double c) : type(TokenType::NUMBER), number(num), line(l), column(c) {}

    // Constructor for OPERATOR token
    Token(TokenType t, double l, double c, char o) : type(t), number(0.0), line(l), column(c), opS(o) {}
};
std::ostream& operator<<(std::ostream& os, const Token& token) {
    switch (token.type) {
        case TokenType::LEFT_PAREN:
            os << "(";
            break;
        case TokenType::RIGHT_PAREN:
            os << ")";
            break;
        case TokenType::OPERATOR:
            os << token.opS;
            break;
        case TokenType::NUMBER:
            os << token.number; // Print the doubles
            break;
        case TokenType::END:
            os << "END";
            break;
        default:
            os << "Unknown";
    }
    return os;
}


#endif // TOKEN_H

