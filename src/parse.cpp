/*#include <iostream>
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

    // Tokenize the input
    lexer.readTokens(str);
    std::queue<Token> tokens = lexer.getTokens();

    // Create a parser with the token vector
    Parser parser(tokens);

    // Parse the S-expression
    AstNode* root = parser.parseSExpression();

    // Evaluate the AST
    double result = evaluate(root);
    // Print the AST in infix form
    printInfix(root, true);
    std::cout << std::endl;

    // Print the result
    std::cout << result << std::endl;
    delete root;

    return 0;
}*/