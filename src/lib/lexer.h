#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
using namespace std;

class Lexer {
public:
    Lexer(const string& input);
    Token* get_next_token();
    ~Lexer();

private:
    const string input_stream;
    int current_position;
    int current_line;
    int current_column;
};

#endif