#include "Parser.h"
#include <memory>

using namespace std;

Parser::Parser()
{
}

Parser::~Parser()
{
    delHeads();
}

void Parser::delHeads()
{
    while (heads.size() != 0)
    {
        AstNode *temp = pop();
        delete temp;
    }
}

void Parser::makeTrees(deque<Token> &x)
{
    while (x.front().type != Token::TokenType::END && !x.empty())
    {
        makeTree(x);
    }
}
void Parser::makeTree(deque<Token> &x)
{
    AstNode *root = nullptr;
    if (x.front().type == Token::TokenType::LEFTP)
    {
        root = SExpress(x);
    }
    else if (x.front().type == Token::TokenType::NUMBER)
    {
        Num *numTree = new Num(stold(x.front().text));
        root = numTree;
        x.pop_front();
    }
    else if (x.front().type == Token::TokenType::IDENTIFIER)
    {
        NodeKey *id = new NodeKey(x.front().text);
        root = id;
        x.pop_front();
    }
    else
    {
        if (x.front().line && x.front().column && x.front().text != "")
            pError(x.front().line, x.front().column, x.front().text);
    }
    heads.push_back(root);
}

AstNode *Parser::SExpress(deque<Token> &x)
{
    x.pop_front(); // pop open parent
    unique_ptr<AstNode> root = nullptr;
    if (x.front().text == "=")
    {
        root.reset(assign(x));
    }
    else if (x.front().type == Token::TokenType::OPERATOR)
    {
        root.reset(ops(x));
    }
    
    else if (x.front().type == Token::TokenType::NUMBER)
    {
        root = unique_ptr<Num>(new Num(stold(x.front().text)));
    }
    else if (x.front().type == Token::TokenType::IDENTIFIER)
    {
        root = unique_ptr<NodeKey>(new NodeKey(x.front().text));
    }
    else
        pError(x.front().line, x.front().column, x.front().text);
    if (x.front().type != Token::TokenType::RIGHTP)
    {
        pError(x.front().line, x.front().column, x.front().text);
    }
    x.pop_front();
    return root.release();
}

AstNode *Parser::assign(deque<Token> &x)
{
    unique_ptr<Op> root(new Op('='));
    NodeKey *temp;
    int counter = 0;
    x.pop_front();
    if (x.front().type != Token::TokenType::IDENTIFIER)
        pError(x.front().line, x.front().column, x.front().text);
    while (x.front().type == Token::TokenType::IDENTIFIER)
    {
        temp = new NodeKey(x.front().text);
        root->addNode(temp);
        x.pop_front();
    }
    if (x.front().type == Token::TokenType::NUMBER)
    {
        Num *temp2 = new Num(stold(x.front().text));
        root->addNode(temp2);
        x.pop_front();
        if (x.front().type != Token::TokenType::RIGHTP)
            pError(x.front().line, x.front().column, x.front().text);
    }
    else if (x.front().type == Token::TokenType::LEFTP)
    {
        AstNode *temp3 = SExpress(x);
        root->addNode(temp3);
        x.pop_front();
    }
    else
        pError(x.front().line, x.front().column, x.front().text);
    if (counter == 1)    
        if (x.front().type == Token::TokenType::RIGHTP)
            pError(x.front().line, x.front().column, x.front().text);

    return root.release();
}

AstNode *Parser::ops(deque<Token> &x)
{
    unique_ptr<Op> root(new Op(x.front().text[0]));
    AstNode *temp = nullptr;
    NodeKey* temp2 = nullptr;
    Num *temp3 = nullptr;
    x.pop_front();
    int counter = 0; // count how many kids there are, throw error if 0

    while (x.front().type == Token::TokenType::LEFTP || x.front().type == Token::TokenType::NUMBER || x.front().type == Token::TokenType::IDENTIFIER )
    {
        if (x.front().type == Token::TokenType::LEFTP)
        {
            temp = SExpress(x);
            root->addNode(temp);
            x.pop_front();
        }
        else if (x.front().type == Token::TokenType::IDENTIFIER)
        {
            temp2 = new NodeKey(x.front().text);
            root->addNode(temp3);
            x.pop_front();
        }
        else if (x.front().type == Token::TokenType::NUMBER)
        {
            temp3 = new Num(stold(x.front().text));
            root->addNode(temp2);
            x.pop_front();
        }
        if (x.front().type == Token::TokenType::END)
                break;
        counter++;
    }
    if (counter < 1)
        pError(x.front().line, x.front().column, x.front().text);
    return root.release();
}

deque<AstNode *> Parser::getHeads()
{
    return heads;
}

AstNode *Parser::pop()
{
    AstNode *temp = heads.front();
    heads.pop_front();
    return temp;
}

void Parser::pError(int l, int c, string text)
{
    throw runtime_error("Unexpected token at line " + to_string(l) + " column " + to_string(c) + ": " + text);
    delHeads();
    exit(2);
}

void Parser::iError(string text)
{
    throw runtime_error("unknown identifier " + text);
    delHeads();
    exit(3);
}

bool Parser::isEmpty() 
{
    return heads.empty();
}