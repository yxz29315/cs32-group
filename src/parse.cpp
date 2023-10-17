#include <iostream>
#include <vector>
#include <stack>

#include "lex.h"
#include "token.h"

// Define an abstract syntax tree (AST) node


int main() {
    std::string input;
    std::string line;

    // Read input from standard input
    while (std::getline(std::cin, line)) {
        input += line + '\n';
    }

    Lexer lexer(input);
    Token* token;

    // Initialize a vector to store tokens
    std::vector<Token*> tokens;

    // Tokenize the input
    do {
        token = lexer.get_next_token();
        if (token->type != TokenType::END) {
            tokens.push_back(token);
        } else {
            free_token(token);
        }
    } while (token->type != TokenType::END);

    // Create a parser with the token vector
    Parser parser(tokens);

    // Parse the S-expression
    AstNode* root = parseSExpression(parser);

    if (root == nullptr) {
        // Handle parse errors
        std::cerr << "Unexpected token at line " << parser.tokens[parser.current_token_index]->line
                  << " column " << parser.tokens[parser.current_token_index]->column << ": "
                  << parser.tokens[parser.current_token_index]->text << std::endl;
        exit(2);
    }

    // Evaluate the AST
    double result = evaluate(root);

    // Print the AST in infix form
    printInfix(root, true);

    // Print the result
    std::cout << result << std::endl;

    return 0;
}

