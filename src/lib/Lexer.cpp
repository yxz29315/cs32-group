#include "Lexer.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void Lexer::readTokens(string inputStr) {
    istringstream stream(inputStr);
    double nextLine = 1;
    double nextCol = 1;
    char currentChar;

    while (stream.get(currentChar)) {

        if (currentChar == '\n') {
            nextLine++;
            nextCol = 1;
            continue;
        }

        if (!isspace(currentChar)) {
            if (currentChar == '(' || currentChar == ')' || currentChar == '+' ||
                currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '=') {
                    Token x;
                    x.line = nextLine;
                    x.column = nextCol;
                    x.type = Token::TokenType::OPERATOR;
                    x.text = "";
                    x.text += currentChar;
                    tokens.push(x);
            }
            else if (isdigit(currentChar)) {
                bool hasDec = false;
                string temp2 = "";
                temp2 += currentChar;
                int col1 = nextCol;

                while ((isdigit(stream.peek()) || stream.peek() == '.')) {
                    if (stream.peek() == '.') {
                        if (hasDec) {
                            cout << "Syntax error on line " << nextLine << " column " << nextCol + 1 << ".\n";
                            exit(1);
                        }
                        else {
							hasDec = true;
                        }
                    }
                    char next;
                    stream.get(next);
                    temp2 += next;
                    nextCol++;
                }

                if (temp2.back() == '.') {
                    cout << "Syntax error on line " << nextLine << " column " << nextCol + 1 << ".\n";
                    exit(1);
                }
                Token y;
                y.line = nextLine;
                y.column = col1;
                y.text = temp2;
                y.type = Token::TokenType::NUMBER;
                tokens.push(y);
            }
            else if (isalpha(currentChar) || currentChar == '_')
            {
                string temp2(1,currentChar);
                int col1 = nextCol;
                while (isalpha(stream.peek()) || isdigit(stream.peek()) || stream.peek() == '_')
                {
                    char next;
                    stream.get(next);
                    temp2 += next;
                    nextCol++;
                }
                Token z;
                z.line = nextLine;
                z.column = col1;
                z.text = temp2;
                z.type = Token::TokenType::NUMBER;
                tokens.push(z);


            }
            else {
                cout << "Syntax error on line " << nextLine << " column " << nextCol << ".\n";
                exit(1);
            }
        }
        nextCol++;
    }
    // Add END token
    Token end;
    end.line = nextLine;
    end.column = nextCol;
    end.type = Token::TokenType::END;
    end.text = "END";
    tokens.push(end);
}


void Lexer::printTokens() {
    
    while (!tokens.empty()) {
        Token cur = tokens.front();
        cout << setfill(' ')  << setw(4) << right << cur.line << setfill(' ')
        << setw(5) << right << cur.column << "  " << cur.text << endl;
        tokens.pop();
    }
}

queue<Token> Lexer::getTokens() {
    return tokens;
}
