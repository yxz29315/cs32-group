#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"

// Define an abstract syntax tree (AST) node

Parser::Parser(vector<Token*>& tokens) : tokens(tokens) {}

// Function to parse an expression
AstNode* Parser::parseExpression() {
    Token* currentToken = tokens[current_token_index];

    if (currentToken->type == Token::TokenType::LEFT_PAREN) {
        current_token_index++; // Consume the opening parenthesis
        AstNode* leftExpr = parseExpression();

        if (leftExpr == nullptr) {
            return nullptr; // Parse error
        }

        currentToken = tokens[current_token_index];

        if (currentToken->type == Token::TokenType::OPERATOR) {
            current_token_index++; // Consume the operator
            AstNode* rightExpr = parseExpression();

            if (rightExpr == nullptr) {
                return nullptr; // Parse error
            }

            currentToken = tokens[current_token_index];
            if (currentToken->type == Token::TokenType::RIGHT_PAREN) {
                current_token_index++; // Consume the closing parenthesis
                AstNode* rootNode = new AstNode(Token::TokenType::OPERATOR, currentToken->text);
                rootNode->left = leftExpr;
                rootNode->right = rightExpr;
                return rootNode;
            } else {
                return nullptr; // Parse error
            }
        } else if (currentToken->type == Token::TokenType::RIGHT_PAREN) {
            current_token_index++; // Consume the closing parenthesis
            return leftExpr; // Return the expression within parentheses
        } else {
            return nullptr; // Parse error
        }
    } else if (currentToken->type == Token::TokenType::NUMBER) {
        current_token_index++; // Consume the number
        return new AstNode(Token::TokenType::NUMBER, currentToken->text);
    } else {
        return nullptr; // Parse error
    }
}

// Function to parse an S-expression
AstNode* Parser::parseSExpression() {
    // A top-level S-expression should contain exactly one expression
    AstNode* expr = parseExpression();

    // Check if there are extra tokens after the S-expression
    if (tokens[current_token_index]->type != Token::TokenType::END) {
        return nullptr; // Parse error
    }

    return expr;
}

AstNode* Parser::parse()
{
    // Parse the S-expression
    AstNode* root = parseSExpression();

    if (root == nullptr) {
        // Handle parse errors
        std::cerr << "Unexpected token at line " << tokens[current_token_index]->line
                  << " column " << tokens[current_token_index]->column << ": "
                  << tokens[current_token_index]->text << std::endl;
        exit(2);
    }

    
    return root;
}