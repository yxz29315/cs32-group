#include <iostream>
#include <cctype>
#include <string>
#include <vector>

#include "lib/lex.h"


Lexer::Lexer(std::istream& input) : input(input), syntaxError(false) {
    // Constructor implementation
}

void Lexer::readNextToken() {
    char currentChar;
    input.get(currentChar);

    // Skip whitespace characters
    while (std::isspace(currentChar)) {
        if (currentChar == '\n') {
            // Update line and reset column when a newline is encountered
            ++tokens.back().line;
            tokens.back().column = 1;
        } else {
            ++tokens.back().column;
        }
        input.get(currentChar);
    }

    if (input.eof()) {
        // Reached the end of input
        tokens.push_back(Token(TokenType::END, tokens.back().line, tokens.back().column + 1));
        return;
    }

    if (currentChar == '(') {
        tokens.push_back(Token(TokenType::LEFT_PAREN, tokens.back().line, tokens.back().column));
    } else if (currentChar == ')') {
        tokens.push_back(Token(TokenType::RIGHT_PAREN, tokens.back().line, tokens.back().column));
    } else if (currentChar == '+') {
        tokens.push_back(Token(TokenType::ADD, tokens.back().line, tokens.back().column));
    } else if (currentChar == '-') {
        tokens.push_back(Token(TokenType::SUBTRACT, tokens.back().line, tokens.back().column));
    } else if (currentChar == '*') {
        tokens.push_back(Token(TokenType::MULTIPLY, tokens.back().line, tokens.back().column));
    } else if (currentChar == '/') {
        tokens.push_back(Token(TokenType::DIVIDE, tokens.back().line, tokens.back().column));
    } else if (std::isdigit(currentChar) || currentChar == '.') {
        // Read a simple floating point number
        std::string number;
        number += currentChar;
        while (input.get(currentChar)) {
            if (std::isdigit(currentChar) || currentChar == '.') {
                number += currentChar;
            } else {
                input.unget();
                break;
            }
        }
        tokens.push_back(Token(std::stod(number), tokens.back().line, tokens.back().column));
    } else {
        // Invalid character, report syntax error
        reportSyntaxError("Invalid character: " + currentChar);
    }

    ++tokens.back().column;
}

void Lexer::skipWhitespace() {
    // Skip whitespace characters
    char currentChar;
    while (input.get(currentChar)) {
        if (std::isspace(currentChar)) {
            if (currentChar == '\n') {
                // Update line and reset column when a newline is encountered
                ++tokens.back().line;
                tokens.back().column = 1;
            } else {
                ++tokens.back().column;
            }
        } else {
            input.unget();
            break;
        }
    }
}

std::vector<Token> Lexer::tokenize() {
    while (true) {
        skipWhitespace();
        readNextToken();

        if (tokens.back().type == TokenType::END) {
            break;
        }
    }

    return tokens;
}

void Lexer::reportSyntaxError(const std::string& message) {
    syntaxError = true;
    std::cerr << "Syntax Error on line " << tokens.back().line
              << " column " << tokens.back().column << ". " << message << std::endl;
}

bool Lexer::hasSyntaxError() const {
    return syntaxError;
}

void Lexer::printTokensAndPositions() const {
    std::cout << "Line  Col  Token" << std::endl;
    for (const Token& token : tokens) {
        std::cout << "   " << token.line << "    " << token.column << "  " << token << std::endl;
    }
}

