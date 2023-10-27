#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "AST.h"
#include "Lexer.h"
#include <queue>
#include <set>

using namespace std;



class Parser {
public:
    Parser(queue<Token> x);
    void makeTree (queue<Token>& x);
    AstNode* popHead();
    bool isEmpty();

private: 
    queue<AstNode*> heads;
    void error(int l, int c, string text) const;
    AstNode* SExpress(queue<Token>& x);
    AstNode* ops(queue<Token>& x);
    AstNode* evalExpress(queue<Token>& x);


};

#endif