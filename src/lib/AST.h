#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class AstNode
{
    public:
        virtual double evaluate(unordered_map<string, double>& list) const = 0;
        virtual void printInfix() const = 0;
        virtual string getKey() = 0;
        virtual ~AstNode() {};
};

class Num : public AstNode {
    public:
        Num(double x);
        virtual double evaluate(unordered_map<string, double>& list) const;
        virtual void printInfix() const;
        virtual string getKey();
    private:
        double val;
       
};

class Op : public AstNode {
    public:
        Op(char y);
        virtual double evaluate(unordered_map<string, double>& list) const;
        virtual void printInfix() const;
        void addNode (AstNode* x);
        virtual string getKey();
        ~Op()
        {
            for (AstNode* x: nodes)
            {
                delete x;
            }
            nodes.clear();
        };
        private:
            char op;
            vector<AstNode*> nodes;
            
};

class NodeKey : public AstNode {
    public:
    NodeKey(string x);
    virtual double evaluate(unordered_map<string, double>& list) const;
    virtual void printInfix() const;
    virtual string getKey();

    private:
    string key;
};




#endif