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
    Parser();
    ~Parser();
    void makeTree (deque<Token>& x);
    void makeTrees(deque<Token>& x);
    AstNode* pop();
    bool isEmpty();
    deque<AstNode*> getHeads();
    void delHeads();

private: 
    deque<AstNode*> heads;
    void pError(int l, int c, string text);
    void iError(string text);
    AstNode* SExpress(deque<Token>& x);
    AstNode* ops(deque<Token>& x);
    AstNode* assign(deque<Token>& x);


};

#endif