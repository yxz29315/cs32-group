#include "Parser.h"

Parser::Parser(queue<Token> x)
{
    while (x.front().text != "END")
        makeTree(x);
}
void Parser::makeTree(queue<Token>& x)
{

    AstNode* root;
        if (x.front().text == "(")
        {
            root = SExpress(x);
        }
        else if (isdigit(x.front().text.at(0)))
        {
            Num* numTree = new Num(stold(x.front().text));
            root = numTree;
            x.pop();
        }
        else
        {
            error(x.front().line, x.front().column, x.front().text);
        }
        heads.push(root);

}

AstNode* Parser::SExpress(queue<Token>& x)
{
    x.pop();
    AstNode* root;
    if (x.front().text == "+" || x.front().text == "-" || x.front().text == "*" || x.front().text == "/")
    {
        root = ops(x);
    }
    else 
    {
        error(x.front().line, x.front().column, x.front().text);
    }
    if (x.front().text != ")")
    {
        error(x.front().line, x.front().column, x.front().text);
    }
    x.pop();
    return root;
}