#include <iostream>
#include <cctype>
#include <string>
#include <vector>

#include "lex.h"
#include "token.h"

Lexer::Lexer(const std::string& input) : input_stream(input), current_position(0), current_line(1), current_column(1) {
}

Token* Lexer::get_next_token() {
    while (current_position < input_stream.length()) {
        char current_char = input_stream[current_position];

        if (current_char == '(') {
            Token* token = create_token(TokenType::LPAREN, current_line, current_column, "(");
            current_position++;
            current_column++;
            return token;
        }
        else if (current_char == ')') {
            Token* token = create_token(TokenType::RPAREN, current_line, current_column, ")");
            current_position++;
            current_column++;
            return token;
        }
        else if (current_char == '+') {
            Token* token = create_token(TokenType::OPERATOR, current_line, current_column, "+");
            current_position++;
            current_column++;
            return token;
        }
        else if (current_char == '-') {
            Token* token = create_token(TokenType::OPERATOR, current_line, current_column, "-");
            current_position++;
            current_column++;
            return token;
        }
        else if (current_char == '*') {
            Token* token = create_token(TokenType::OPERATOR, current_line, current_column, "*");
            current_position++;
            current_column++;
            return token;
        }
        else if (current_char == '/') {
            Token* token = create_token(TokenType::OPERATOR, current_line, current_column, "/");
            current_position++;
            current_column++;
            return token;
        }
        else if (std::isdigit(current_char) || (current_char == '.' && std::isdigit(input_stream[current_position + 1]))) {
            // Recognize numbers
            int start = current_position;
            while (current_position < input_stream.length() &&
                (std::isdigit(input_stream[current_position]) || input_stream[current_position] == '.'))
            {
                current_position++;
                current_column++;
            }
            std::string number_text = input_stream.substr(start, current_position - start);
            Token* token = create_token(TokenType::NUMBER, current_line, current_column - number_text.length() + 1, number_text);
            return token;
        }
        else if (std::isspace(current_char)) {
            if (current_char == '\n') {
                current_line++;
                current_column = 1;
            }
            else {
                current_column++;
            }
            current_position++;
        }
        else {
            std::cerr << "Syntax error on line " << current_line << " column " << current_column << "." << std::endl;
            exit(1);
        }
    }

    return create_token(TokenType::END, current_line, current_column, "END");
}

int main() {
    std::string input;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        input += line + '\n';
    }

    Lexer lexer(input);
    Token* token;

    do {
        token = lexer.get_next_token();
        std::cout << std::right << std::setw(4) << token->line << std::setw(6) << token->column << "  " << token->text << std::endl;
        free_token(token);
    } while (token->type != TokenType::END);

    return 0;
}
