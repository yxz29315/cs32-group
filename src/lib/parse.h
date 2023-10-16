#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
using namespace std;

class AstNode {
public:
    TokenType type;
    string text;
    AstNode* left;
    AstNode* right;
};

class Parser {
public:
    Parser(vector<Token*>& tokens);
    AstNode* parse();
    ~Parser();

private:
    vector<Token*> tokens;
    size_t current_token_index;
};

#endif