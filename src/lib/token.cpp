#include "token.h"

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