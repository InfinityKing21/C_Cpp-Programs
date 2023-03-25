#include<iostream>
#include<exception>
#include"expression.hpp"

using std::cin, std::cout, std::cerr;
using std::string;
using std::runtime_error;

int main()
{
    const calculator c;

    cout << "Enter expression: ";
    string expression;
    getline(cin, expression);

    try
    {
        cout << c.getResult(expression);
    }
    catch(runtime_error &e)
    {
        cerr << e.what();
    }

    getchar();
    return 0;
}
