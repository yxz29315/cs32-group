#include <iostream>
#include <sstream>
#include "lib/Lexer.h"

int main() {
    // Read input from standard input
    char ch;
    std::string str = "\0";

    while (std::cin.get(ch)) {
        str += ch;
    }

    // Create a lexer with the input
    Lexer lexer;
    lexer.readTokens(str);
    // Print the tokens
    lexer.printTokens();

    return 0;
}
