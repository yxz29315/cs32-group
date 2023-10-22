#include <iostream>
#include <sstream>
#include "lib/Lexer.h"

int main() {
    std::cout << "Running main\n";
    // Read input from standard input
    std::string input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input += line;
        input += '\n';  // Add newline for line separation
    }

    // Create a lexer with the input
    std::istringstream inputStream(input);
    Lexer lexer(inputStream);
    std::cout << "Lexer created\n";
    lexer.readTokens();
    // Print the tokens
    lexer.printTokens();

    return 0;
}
