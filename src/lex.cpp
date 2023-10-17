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
        // Reached the end of input
        return;
    }

    currentChar = input.peek();

    if (currentChar == '(') {
        tokens.push_back(Token(TokenType::LEFT_PAREN, tokens.back().line, tokens.back().column));
        input.ignore(); // Consume the character
    } else if (currentChar == ')') {
        tokens.push_back(Token(TokenType::RIGHT_PAREN, tokens.back().line, tokens.back().column));
        input.ignore(); // Consume the character
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
        tokens.push_back(Token(TokenType::OPERATOR, tokens.back().line, tokens.back().column, currentChar));
        input.ignore(); // Consume the character
    } else if (std::isdigit(currentChar) || currentChar == '.') {
        // Read a floating-point number
        std::string number;
        while (!input.eof() && (std::isdigit(input.peek()) || input.peek() == '.')) {
            number += input.get();
        }
	tokens.push_back(Token(TokenType::NUMBER, tokens.back().line, tokens.back().column, number));
    } else {
        // Invalid character, report syntax error and consume it
        reportSyntaxError("Invalid character: " + currentChar);
        ++tokens.back().column;
        input.ignore(); // Consume the character
    }
    
    ++tokens.back().column;

    // Check for END token after pushing the token
    if (input.eof()) {
        tokens.push_back(Token(TokenType::END, tokens.back().line, tokens.back().column));
    }
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

