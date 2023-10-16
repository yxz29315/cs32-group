#include <iostream>
#include <cctype>
#include <string>
#include <vector>

#include "lib/lex.h"
#include "lib/token.h"
#include "lex.h"

Lexer::Lexer(std::istream& input) : input(input), syntaxError(false) {
    // Constructor implementation
    // Initialize other member variables here if needed
}

void Lexer::readNextToken() {
    // Implement token recognition logic
}

void Lexer::skipWhitespace() {
    // Implement whitespace skipping logic
}

std::vector<Token> Lexer::tokenize() {
    // Implement the overall tokenization process
    // Call readNextToken in a loop until END token is reached
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

