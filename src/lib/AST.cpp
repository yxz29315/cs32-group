#include "AST.h"

Num::Num(double x)
{
    val = x;
}

double Num::evaluate(unordered_map<string, double>& list) const {
    return val;
}

void Num::printInfix() const {
    cout << val;
}

Op::Op(char y)
{
    op = y;
}

void Op::addNode(AstNode* x)
{
    nodes.push_back(x);
}

double Op::evaluate(unordered_map<string, double>& list) const {
    double ans;
    switch(op)
    {
        case '+':
            for (AstNode* x: nodes)
            {
                ans += x->evaluate(list);
            }
            break;
        case '-':
            for (AstNode* x: nodes)
            {
                ans -= x->evaluate(list);
            }
            break;

        case '*':
            for (AstNode* x: nodes)
            {
                ans *= x->evaluate(list);
            }
            break;
        case '/':
            for (AstNode* x: nodes)
            {
                if (x->evaluate(list) == 0)
                {
                    throw runtime_error("Runtime error: division by zero.");
                }
                ans /= x->evaluate(list);
            }
    }
    return ans;
}

void Op::printInfix() const
{
    if (nodes.empty())
        return;
    cout << '(';
    for (AstNode* x: nodes)
    {
        if (x == nodes[0])
            x->printInfix();
        else
        {
            cout << ' ' << op << ' ';
            x->printInfix();
        }
    }
    cout << ')';
}

NodeKey::NodeKey(string x)
{
    key = x;
}

double NodeKey::evaluate(unordered_map<string, double>& list) const {
    if (list.find(key) == list.end())
        throw runtime_error("Runtime error: unknown key " + key);
    return list[key];   
}

void NodeKey::printInfix() const {
    cout << key;
}

string NodeKey::getKey()
{
    return key;
}