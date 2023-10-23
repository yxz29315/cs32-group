#ifndef AST_H
#define AST_H
#include "Lexer.h"
#include "Parser.h"
#include <vector>
using namespace std;



class AstNode {
public:
    Token::TokenType type;
    std::string text;
    AstNode* left;
    AstNode* right;

    AstNode(Token::TokenType t, const std::string& txt) : type(t), text(txt), left(nullptr), right(nullptr) {}
};

// Function to parse an S-expression
AstNode* parseSExpression(Lexer& lexer);

// Function to parse an expression
AstNode* parseExpression(Lexer& lexer);

// Function to evaluate an AST node
double evaluate(AstNode* node);

// Function to print an AST in infix form
void printInfix(AstNode* node, bool printParentheses = false);

#endif
