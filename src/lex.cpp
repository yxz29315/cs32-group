#include <iostream>
#include <sstream>
#include "lib/Lexer.h"

int main() {
    // Read input from standard input
    std::string input;
    std::string line;

    while (!std::cin.eof()) {
        if (std::getline(std::cin, line)) {
            input += line;
            input += "\n";
            //std::cout<< "reading: '" << line << "'\n";
        }
    }

    // Create a lexer with the input
    std::istringstream inputStream(input);
    Lexer lexer(inputStream);
    lexer.readTokens();
    // Print the tokens
    lexer.printTokens();

    return 0;
}
