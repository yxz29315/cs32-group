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
    AstNode* pop();
    bool isEmpty();
    queue<AstNode*> getHeads();

private: 
    queue<AstNode*> heads;
    void pError(int l, int c, string text);
    AstNode* SExpress(queue<Token>& x);
    AstNode* ops(queue<Token>& x);
    AstNode* evalExpress(queue<Token>& x);


};

#endif