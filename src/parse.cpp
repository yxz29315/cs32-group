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
    std::queue<Token> tokens = lexer.getTokens();

    // Create a parser with the token vector
    Parser parser(tokens);
    queue<AstNode*> temp = parser.getHeads();
    while (temp.size() != 0)
    {
        AstNode* root = parser.pop();
        root->printInfix();
        cout << endl;
        try
        {
            double result = root->evaluate(list);
            delete root;
            cout << result << endl; 
        }
        catch(const runtime_error& error)
        {
            cout << error.what() << '\n';
            exit(3);
        }
        
        
    }
    return 0;


   
   
}