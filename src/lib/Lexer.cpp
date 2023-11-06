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

        if (!isspace(currentChar)) { // checking for space, if not check for operators
            if (currentChar == '(' || currentChar == ')' || currentChar == '+' ||
                currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '=') {
                    Token x;
                    if (currentChar == '(')
                    {
                        x.type = Token::TokenType::LEFTP;
                        x.text = "(";
                    }
                    else if (currentChar == ')')
                    {
                        x.type = Token::TokenType::RIGHTP;
                        x.text = ")";
                    }
                    else
                    {
                        x.type = Token::TokenType::OPERATOR;
                        x.text = "";
                        x.text += currentChar;
                    }
                    x.line = nextLine;
                    x.column = nextCol;
                    
                    tokens.push_back(x);
            }
            else if (isdigit(currentChar)) { // Checking for numbers
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
                tokens.push_back(y);
            }
            else if (isalpha(currentChar) || currentChar == '_') // Checking for identifiers
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
                tokens.push_back(z);


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
    tokens.push_back(end);
}


void Lexer::printTokens() {
    
    while (!tokens.empty()) {
        Token cur = tokens.front();
        cout << setfill(' ')  << setw(4) << right << cur.line << setfill(' ')
        << setw(5) << right << cur.column << "  " << cur.text << endl;
        tokens.pop_front();
    }
}

deque<Token> Lexer::getTokens() {
    return tokens;
}
