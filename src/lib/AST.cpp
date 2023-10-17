#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream> // Include this header for std::istringstream
#include "AST.h"
#include <vector>
using namespace std;


// Function to parse an S-expression
AstNode* parseSExpression(Parser& parser) {
    // A top-level S-expression should contain exactly one expression
    AstNode* expr = parseExpression(parser);

    // Check if there are extra tokens after the S-expression
    if (parser.tokens[parser.current_token_index]->type != TokenType::END) {
        return nullptr; // Parse error
    }

    return expr;
}

// Function to parse an expression
AstNode* parseExpression(Parser& parser) {
    Token* currentToken = parser.tokens[parser.current_token_index];

    if (currentToken->type == TokenType::LEFT_PAREN) {
        parser.current_token_index++; // Consume the opening parenthesis
        AstNode* leftExpr = parseExpression(parser);

        if (leftExpr == nullptr) {
            return nullptr; // Parse error
        }

        currentToken = parser.tokens[parser.current_token_index];

        if (currentToken->type == TokenType::OPERATOR) {
            parser.current_token_index++; // Consume the operator
            AstNode* rightExpr = parseExpression(parser);

            if (rightExpr == nullptr) {
                return nullptr; // Parse error
            }

            currentToken = parser.tokens[parser.current_token_index];
            if (currentToken->type == TokenType::RIGHT_PAREN) {
                parser.current_token_index++; // Consume the closing parenthesis
                AstNode* rootNode = new AstNode(TokenType::OPERATOR, currentToken->text);
                rootNode->left = leftExpr;
                rootNode->right = rightExpr;
                return rootNode;
            } else {
                return nullptr; // Parse error
            }
        } else if (currentToken->type == TokenType::RIGHT_PAREN) {
            parser.current_token_index++; // Consume the closing parenthesis
            return leftExpr; // Return the expression within parentheses
        } else {
            return nullptr; // Parse error
        }
    } else if (currentToken->type == TokenType::NUMBER) {
        parser.current_token_index++; // Consume the number
        return new AstNode(TokenType::NUMBER, currentToken->text);
    } else {
        return nullptr; // Parse error
    }
}

// Function to evaluate an AST node
double evaluate(AstNode* node) {
    if (node->type == TokenType::NUMBER) {
        return std::stod(node->text);
    } else {
        double leftValue = evaluate(node->left);
        double rightValue = evaluate(node->right);
        if (node->text == "+") {
            return leftValue + rightValue;
        } else if (node->text == "-") {
            return leftValue - rightValue;
        } else if (node->text == "*") {
            return leftValue * rightValue;
        } else if (node->text == "/") {
            if (rightValue != 0) {
                return leftValue / rightValue;
            } else {
                std::cerr << "Runtime error: division by zero." << std::endl;
                exit(3);
            }
        }
    }
    return 0.0;
}

// Function to print an AST in infix form
void printInfix(AstNode* node, bool printParentheses) {
    if (node->type == TokenType::NUMBER) {
        std::cout << node->text;
    } else {
        if (printParentheses) {
            std::cout << "(";
        }
        printInfix(node->left, true);
        std::cout << " " << node->text << " ";
        printInfix(node->right, true);
        if (printParentheses) {
            std::cout << ")";
        }
    }
}
