#include <iostream>
#include <vector>
#include <stack>

#include "lexer.h"
#include "token.h"

// Define an abstract syntax tree (AST) node
class AstNode {
public:
    TokenType type;
    std::string text;
    AstNode* left;
    AstNode* right;

    AstNode(TokenType t, const std::string& txt) : type(t), text(txt), left(nullptr), right(nullptr) {}
};

// Function to parse an S-expression
AstNode* parseSExpression(Lexer& lexer);

// Function to parse an expression
AstNode* parseExpression(Lexer& lexer);

// Function to evaluate an AST node
double evaluate(AstNode* node);

// Function to print an AST in infix form
void printInfix(AstNode* node, bool printParentheses = false);

int main() {
    std::string input;
    std::string line;

    // Read input from standard input
    while (std::getline(std::cin, line)) {
        input += line + '\n';
    }

    Lexer lexer(input);
    Token* token;

    // Initialize a vector to store tokens
    std::vector<Token*> tokens;

    // Tokenize the input
    do {
        token = lexer.get_next_token();
        if (token->type != TokenType::END) {
            tokens.push_back(token);
        } else {
            free_token(token);
        }
    } while (token->type != TokenType::END);

    // Create a parser with the token vector
    Parser parser(tokens);

    // Parse the S-expression
    AstNode* root = parseSExpression(parser);

    if (root == nullptr) {
        // Handle parse errors
        std::cerr << "Unexpected token at line " << parser.tokens[parser.current_token_index]->line
                  << " column " << parser.tokens[parser.current_token_index]->column << ": "
                  << parser.tokens[parser.current_token_index]->text << std::endl;
        exit(2);
    }

    // Evaluate the AST
    double result = evaluate(root);

    // Print the AST in infix form
    printInfix(root, true);

    // Print the result
    std::cout << result << std::endl;

    return 0;
}

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

    if (currentToken->type == TokenType::LPAREN) {
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
            if (currentToken->type == TokenType::RPAREN) {
                parser.current_token_index++; // Consume the closing parenthesis
                AstNode* rootNode = new AstNode(TokenType::OPERATOR, currentToken->text);
                rootNode->left = leftExpr;
                rootNode->right = rightExpr;
                return rootNode;
            } else {
                return nullptr; // Parse error
            }
        } else if (currentToken->type == TokenType::RPAREN) {
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
