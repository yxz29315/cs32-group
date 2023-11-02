#include "Parser.h"

using namespace std;
Parser::Parser(queue<Token> x)
{
    while (x.front().type != Token::TokenType::END)
        makeTree(x);
}
void Parser::makeTree(queue<Token>& x)
{

    AstNode* root;
        if (x.front().text == "(")
        {
            root = SExpress(x);
        }
        else if (x.front().type == Token::TokenType::NUMBER)
        {
            Num* numTree = new Num(stold(x.front().text));
            root = numTree;
            x.pop();
        }
        else
        {
            pError(x.front().line, x.front().column, x.front().text);
        }
        heads.push(root);

}

AstNode* Parser::SExpress(queue<Token>& x)
{
    x.pop();
    AstNode* root;
    if (x.front().type == Token::TokenType::OPERATOR)
    {
        root = ops(x);
    }
    else 
    {
        pError(x.front().line, x.front().column, x.front().text);
    }
    if (x.front().text != ")")
    {
        pError(x.front().line, x.front().column, x.front().text);
    }
    x.pop();
    return root;
}

AstNode* Parser::ops(queue<Token>& x)
{
    Op* root = new Op(x.front().text[0]);
    AstNode* temp;
    Num* temp2;
    int counter; // count how many kids there are, throw error if 0 or 1

    x.pop(); // consume left paren
    while (x.front().type != Token::TokenType::OPERATOR)
    {
        if (x.front().text == "(")
        {
            temp = SExpress(x);
            root->addNode(temp);
            x.pop();
            counter++;
        }
        else 
        {
            temp2 = new Num(stold(x.front().text));
            root->addNode(temp2);
            x.pop();
            counter++;
        }
        if (x.front().type == Token::TokenType::END)
            break;
    }
    if (counter < 1)
        pError(x.front().line, x.front().column, x.front().text);
    return root;


}

queue<AstNode*> Parser::getHeads()
{
    return heads;
}

AstNode* Parser::pop()
{
    AstNode* temp = heads.front();
    heads.pop();
    return temp;
}

void Parser::pError(int l, int c, string text)
{
    cout << "Unexpected token at line " << l << " column " << c << ": " << text << endl;
	exit(2);
}