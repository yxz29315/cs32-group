Authors: Yuxiang Zhang, Ryan Vo

This calculator has 2 components: the lexer, responsible for converting raw text into a sequence of tokens, and the parser, which constructs an abstract syntax tree and performs calculations on input S-Expressions.

The Lexer:
The Lexer processes standard input during its construction, forming a queue of Token objects. These tokens are limited to specific strings: "(", ")", "+", "-", "/", "*", and valid numbers. These tokens are collected for future evaluation by a component such as the Parser.

The Parser:
The Parser collects a queue of tokens, including token line, token column, and token text, from the Lexer. It then constructs an abstract syntax tree using the Parser::parse() function. This tree enables the calculation of the desired S-Expression using the virtual function evaluateNode(). The Parser also generates and prints the original S-Expression in infix form using the virtual function printInfix(). In the main function, a try-catch block is used to handle runtime errors (exit code 3). Parse errors (exit code 2) are thrown as they occur during AST construction and calculation.