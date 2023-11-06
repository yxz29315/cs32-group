#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

#include "lib/Lexer.h"
#include "lib/Parser.h"

int main() {
    char ch;
	std::string str = "\0";

	while (std::cin.get(ch)){
		str += ch;
	}

    Lexer lexer;
    unordered_map<string, double> list;

    // Tokenize the input
    lexer.readTokens(str);
    std::deque<Token> tokens = lexer.getTokens();

    // Create a parser with the token vector
    Parser parser;
    try {
        parser.makeTrees(tokens);
    }
    catch (const runtime_error& error)
    {
        cout << error.what() << '\n';
        exit(2);
    }
    deque<AstNode*> temp = parser.getHeads();
    while (!temp.empty())
    {
        AstNode* root = parser.pop();
        root->printInfix();
        cout << endl;
        try
        {
            double result = root->evaluate(list);
            delete root;
            root = nullptr;
            cout << result << endl; 
        }
        catch(const runtime_error& error)
        {
            delete root;
            root = nullptr;
            cout << error.what() << '\n';
            exit(3);
        }
        
        
    }
    return 0;


   
   
}