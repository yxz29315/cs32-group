#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream> // Include this header for std::istringstream

#include "lib/lex.h"

int main() {
    // Create an input stream (you can replace this with your input source)
    std::istringstream input("(+(-2 4.444 )\n32(* 5 13.45)(");

    // Create a Lexer object
    Lexer lexer(input);

    // Tokenize the input
    std::vector<Token> tokens = lexer.tokenize();

    // Print tokens and positions
    lexer.printTokensAndPositions();

    // Check for syntax errors
    if (lexer.hasSyntaxError()) {
        std::cerr << "Syntax error detected." << std::endl;
        return 1; // Exit with an error code
    }

    return 0; // Exit with a success code
}

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

