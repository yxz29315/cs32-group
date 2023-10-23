#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream> // Include this header for std::istringstream
#include <vector>
using namespace std;



// Function to evaluate an AST node
double evaluate(AstNode* node) {
    if (node->type == Token::TokenType::NUMBER) {
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
    if (node->type == Token::TokenType::NUMBER) {
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
