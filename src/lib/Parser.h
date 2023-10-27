#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "AST.h"
#include "Lexer.h"
using namespace std;



class Parser {
public:
    Parser(queue<Token>& tokens);
    AstNode* parse();
    ~Parser();
    
    // Function to parse an S-expression
    AstNode* parseSExpression();

    // Function to parse an expression
    AstNode* parseExpression();

private:
    queue<Token> tokens;
    size_t current_token_index;
    AstNode* rootNode;
};

#endif