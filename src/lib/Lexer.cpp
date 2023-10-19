#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream> // Include this header for std::istringstream

#include "Lexer.h"


Lexer::Lexer(std::istream& input) : input(input), syntaxError(false) {
    // Constructor implementation
    tokens.push_back(Token(TokenType::END, 1, 1));
}

void Lexer::readNextToken() {
    char currentChar;

    // Skip whitespace characters
    while (std::isspace(input.peek())) {
        if (input.peek() == '\n') {
            // Update line and reset column when a newline is encountered
            ++tokens.back().line;
            tokens.back().column = 1;
        } else {
            ++tokens.back().column;
        }
        input.ignore();
    }

    if (input.eof()) {
        ++tokens.back().line;
        tokens.back().column = 1;
        return;
    }

    currentChar = input.peek();

    if (currentChar == '(') {
        tokens.insert(tokens.end() - 1, Token(TokenType::LEFT_PAREN, tokens.back().line, tokens.back().column));
        input.ignore(); // Consume the character
    } else if (currentChar == ')') {
        tokens.insert(tokens.end() - 1, Token(TokenType::RIGHT_PAREN, tokens.back().line, tokens.back().column));
        input.ignore(); // Consume the character
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
        tokens.insert(tokens.end() - 1, Token(TokenType::OPERATOR, tokens.back().line, tokens.back().column, "" + currentChar));
        input.ignore(); // Consume the character
    } else if (std::isdigit(currentChar) || currentChar == '.') {
        // Read a floating-point number
        std::string number;
        while (!input.eof() && (std::isdigit(input.peek()) || input.peek() == '.')) {
            number += input.get();
        }
        double num = std::stod(number); // Convert the string to a double
        tokens.insert(tokens.end() - 1, Token(num, tokens.back().line, tokens.back().column));
    } else {
        // Invalid character, report syntax error and consume it
        reportSyntaxError("Invalid character: " + currentChar);
        input.ignore(); // Consume the character
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
    for (const Token& token : tokens) {
        // Print line and column numbers followed by the token
        std::cout << "    " << token.line << "    " << token.column << "  " << token << std::endl;
    }
}

