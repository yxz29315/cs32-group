#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

// Enum to represent different token types
enum class TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NUMBER,
    END
};

// Structure to represent a token
struct Token {
    TokenType type;
    double number; // Store numbers as doubles
    double line;   // Use double for line
    double column; // Use double for column

    // Constructor for other token types
    Token(TokenType t, double l, double c) : type(t), number(0.0), line(l), column(c) {}

    // Constructor for NUMBER token
    Token(double num, double l, double c) : type(TokenType::NUMBER), number(num), line(l), column(c) {}
};

// Have the << operator for Token to print it
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Line " << token.line << "  Col " << token.column << "  ";
    switch (token.type) {
        case TokenType::LEFT_PAREN:
            os << "(";
            break;
        case TokenType::RIGHT_PAREN:
            os << ")";
            break;
        case TokenType::ADD:
            os << "+";
            break;
        case TokenType::SUBTRACT:
            os << "-";
            break;
        case TokenType::MULTIPLY:
            os << "*";
            break;
        case TokenType::DIVIDE:
            os << "/";
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

