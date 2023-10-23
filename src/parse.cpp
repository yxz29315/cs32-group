#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

#include "Lib/Lexer.h"
#include "Lib/Parser.h"

// Define an abstract syntax tree (AST) node


int main() {
    std::string input;
    std::string line;

    // Read input from standard input
    while (std::getline(std::cin, line)) {
        input += line + '\n';
    }

    std::istringstream inputStream(input);
    Lexer lexer(inputStream);

    // Initialize a vector to store tokens

    // Tokenize the input
    lexer.readTokens();
    std::vector<Token*> vect = lexer.returnTokens();

    // Create a parser with the token vector
    Parser parser(vect);

    // Parse the S-expression
    AstNode* root = parser.parseSExpression();


    // Evaluate the AST
    double result = evaluate(root);

    // Print the AST in infix form
    printInfix(root, true);

    // Print the result
    std::cout << result << std::endl;

    return 0;
}
