#include <iostream>
#include "lib/Lexer.h"

int main() {
    // Read input from standard input
    std::string input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input += line;
        input += '\n';  // Add newline for line separation
    }

    // Create a lexer with the input
    Lexer lexer(input);

    // Print the tokens
    lexer.printTokens();

    return 0;
}

