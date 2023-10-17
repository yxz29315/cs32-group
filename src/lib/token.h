#ifndef TOKEN_H
#define TOKEN_H

using namespace std;
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
    string text; // Store numbers as doubles
    double line;   // Use double for line
    double column; // Use double for column

    // Constructor for other token types
    Token(TokenType t, double l, double c, string o = "") : type(t), text(o), line(l), column(c) {}

    // Constructor for NUMBER token
    Token(double num, double l, double c) : type(TokenType::NUMBER), text(to_string(num)), line(l), column(c) {}

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
            os << token.text;
            break;
        case TokenType::NUMBER:
            os << token.text; // Print the doubles
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

