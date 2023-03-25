# Expression Evaluator

This project is meant to work as a basic calculator supporting the following list of features: <br />

-   [x] Get Postfix expression from infix
-   [x] Arithmetic operators: +, -, \*, /, %, ^
-   [ ] Support for unary and bitwise operators
-   [ ] Input expressions in prefix or postfix
-   [ ] Self-defined binary operators defined in terms of already existing operators
-   [ ] Unary function, e.g. f(x) = 2 \* x
-   [ ] Handling arrow keys

## Important

-   **Reliability is untested**
-   ^ has been used for power instead of bitwise xor. This may change in the future when bitwise xor gets implemented.

## Usage

This project was compiled and linked using gcc (GCC) 12.2.1 20230201 on a linux environment. <br />
Example using the `makefile` (GNU Make 4.4.1) provided; :

```
make
./calculator.o
```

## Project Motivation

A more basic form of this project was given to me as a challenge from a friend. The challenge was to create a program capable of taking in expressions and evaluating them.
