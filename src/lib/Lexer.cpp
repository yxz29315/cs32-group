#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
Lexer::Lexer(std::istream& input) : input(input) {
    // Initialize your lexer as needed
}

void Lexer::skipWhitespace() {
    char c = input.peek();
    while (std::isspace(c)) {
        input.get();
        c = input.peek();
    }
}

Token Lexer::getNextToken() {
    skipWhitespace();

    char currentChar = input.peek();
    Token token;

    token.line = 1; // Initialize line and column numbers here
    token.column = 1;

    if (currentChar == '(') {
        token.type = Token::TokenType::LEFT_PAREN;
        token.text = "(";
        input.get();
    } else if (currentChar == ')') {
        token.type = Token::TokenType::RIGHT_PAREN;
        token.text = ")";
        input.get();
    } else if (currentChar == '+') {
        token.type = Token::TokenType::OPERATOR;
        token.text = "+";
        input.get();
    } else if (currentChar == '-') {
        token.type = Token::TokenType::OPERATOR;
        token.text = "-";
        input.get();
    } else if (currentChar == '*') {
        token.type = Token::TokenType::OPERATOR;
        token.text = "*";
        input.get();
    } else if (currentChar == '/') {
        token.type = Token::TokenType::OPERATOR;
        token.text = "/";
        input.get();
    } else if (std::isdigit(currentChar) || currentChar == '.') {
        token.type = Token::TokenType::NUMBER;
        token.text = "";

        while (std::isdigit(currentChar) || currentChar == '.') {
            token.text += currentChar;
            input.get();
            currentChar = input.peek();
        }

        // Store numbers as doubles
        token.value = std::stod(token.text);
    } else {
        std::cerr << "Syntax error on line " << token.line << " column " << token.column << ".\n";
        exit(1);
    }

    return token;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token;

    do {
        token = getNextToken();
        tokens.push_back(token);
    } while (token.type != Token::TokenType::END);

    return tokens;
}

void Lexer::printTokens() {
    std::vector<Token> tokens = tokenize();

    int currentLine = 1; // Initialize line and column numbers for output
    int currentColumn = 1;

    for (const Token& token : tokens) {
        if (token.text == "\n") {
            // Handle newlines
            currentLine++;
            currentColumn = 1;
        } else {
            std::cout << std::setw(4) << currentLine << std::setw(4) << currentColumn << " " << token.text;

            if (token.type == Token::TokenType::NUMBER) {
                std::cout << " (" << token.value << ")";
            }

            std::cout << std::endl;

            // Update the column number
            currentColumn += token.text.length();
        }
    }
}

