#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "AST.h"
#include "Lexer.h"
#include <deque>
#include <set>

using namespace std;



class Parser {
public:
    Parser(deque<Token> x);
    ~Parser();
    void makeTree (deque<Token>& x);
    AstNode* pop();
    bool isEmpty();
    deque<AstNode*> getHeads();

private: 
    deque<AstNode*> heads;
    void pError(int l, int c, string text);
    AstNode* SExpress(deque<Token>& x);
    AstNode* ops(deque<Token>& x);
    AstNode* assign(deque<Token>& x);


};

#endif