#include "Parser.h"

using namespace std;
Parser::Parser(deque<Token> x)
{
    while (x.front().type != Token::TokenType::END)
        makeTree(x);
}

Parser::~Parser()
{
    while (heads.size() != 0)
    {
        AstNode* temp = pop();
        delete temp;
    }
}
void Parser::makeTree(deque<Token>& x)
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
            x.pop_front();
        }
        else if (x.front().type == Token::TokenType::IDENTIFIER)
        {
            NodeKey* id = new NodeKey(x.front().text);
            root = id;
            x.pop_front();
        }
        else
        {
            pError(x.front().line, x.front().column, x.front().text);
        }
        heads.push_back(root);

}

AstNode* Parser::SExpress(deque<Token>& x)
{
    x.pop_front();
    AstNode* root;
    if (x.front().text == "=")
    {
        root = assign(x);
    }
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
    x.pop_front();
    return root;
}

AstNode* Parser::assign(deque<Token>& x)
{

    Op* root = new Op('=');
    NodeKey* temp;
    int counter = 0;
    x.pop_front();
    if (x.front().type != Token::TokenType::IDENTIFIER)
        pError(x.front().line, x.front().column, x.front().text);
    while (x.front().type == Token::TokenType::IDENTIFIER)
    {
        temp = new NodeKey(x.front().text);
        root->addNode(temp);
        x.pop_front();
        counter++;
    }
    if (counter == 0)
    {
        pError(x.front().line, x.front().column, x.front().text);
    }

    if (x.front().type == Token::TokenType::NUMBER)
    {
        Num* temp2 = new Num(stold(x.front().text));
        root->addNode(temp2);
        x.pop_front();
    }
    else if (x.front().text == "(")
    {
        AstNode* temp3 = SExpress(x);
        root->addNode(temp3); 
    }
    else if (counter == 0)
        pError(x.front().line, x.front().column, x.front().text);


    if (x.front().text != ")")
        pError(x.front().line, x.front().column, x.front().text);
    

    return root;
}

AstNode* Parser::ops(deque<Token>& x)
{
    Op* root = new Op(x.front().text[0]);
    AstNode* temp;
    Num* temp2;
    int counter = 0; // count how many kids there are, throw error if 0

    x.pop_front(); // consume left paren
    while (x.front().type != Token::TokenType::OPERATOR)
    {
        if (x.front().text == "(")
        {
            temp = SExpress(x);
            root->addNode(temp);
            x.pop_front();
            counter++;
        }
        else 
        {
            temp2 = new Num(stold(x.front().text));
            root->addNode(temp2);
            x.pop_front();
            counter++;
        }
        if (x.front().type == Token::TokenType::END)
            break;
    }
    if (counter == 0)
        pError(x.front().line, x.front().column, x.front().text);
    return root;


}

deque<AstNode*> Parser::getHeads()
{
    return heads;
}

AstNode* Parser::pop()
{
    AstNode* temp = heads.front();
    heads.pop_front();
    return temp;
}

void Parser::pError(int l, int c, string text)
{
    throw runtime_error("Unexpected token at line " + to_string(l) + " column " + to_string(c) + ": " + text);
	exit(2);
}

void Parser::iError(string text)
{
    throw runtime_error("unknown identifier " + text);
	exit(3);
}
