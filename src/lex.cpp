#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream> // Include this header for std::istringstream

#include "lib/Lexer.h"


int main() {
    // Create an input stream (you can replace this with your input source)
    std::istringstream input("(+(-2 4.444 )\n32(* 5 13.45)(");

    // Create a Lexer object
    Lexer lexer(input);

    // Tokenize the input
    std::vector<Token> tokens = lexer.tokenize();

    // Print tokens and positions
    lexer.printTokensAndPositions();

    // Check for syntax errors
    if (lexer.hasSyntaxError()) {
        std::cerr << "Syntax error detected." << std::endl;
        return 1; // Exit with an error code
    }

    return 0; // Exit with a success code
}
