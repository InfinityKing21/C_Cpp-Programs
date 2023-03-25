#include<string>
#include<stack>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<exception>
#include<sstream>
#include<cctype>
#include"expression.hpp"

using std::string;
using std::stack;
using std::vector;
using std::any_of;
using std::remove;
using std::runtime_error;
using std::stringstream;

calculator::calculator():
    leftEnclosure{"{"},
    rightEnclosure{"}"},
    operators{'^', '*', '/', '%', '+', '-'},
    openParentheses{{'(', ')'}, {'{', '}'}, {'[', ']'}},
    closeParentheses{{')', '('}, {'}', '{'}, {']', '['}}
{ }

long long calculator::getResult(const string expression) const
{
    checkExpression(expression);

    if(isAlgebraicExpression(expression))
        throw runtime_error("Cannot evaluate algebraic expressions.");

    auto terms = getPostfixTerms(expression);

    stack<long long> evaluation;

    for(auto &term : terms)
    {
        if(isOperator(term))
        {
            const auto &op = term[0];

            auto rightOperand = evaluation.top();
            evaluation.pop();

            auto leftOperand = evaluation.top();
            evaluation.pop();

            auto result = evaluateOperator(leftOperand, op, rightOperand);
            evaluation.push(result);
        }
        else
        {
            auto number = stringToLongLong(term);
            evaluation.push(number);
        }
    }

    return evaluation.top();
}

void calculator::checkExpression(const string &expression) const
{
    auto parenthesisPairs = countMatchingParenthesis(expression);

    if(parenthesisPairs > 0)
        throw runtime_error("Opening parenthesis more in number than closing parenthesis");

    if(parenthesisPairs < 0)
        throw runtime_error("Closing parenthesis more in number than opening parenthesis");

    if(!hasRelevantTerms(expression))
        throw runtime_error("Invalid expression");
}

long long calculator::countMatchingParenthesis(const string &expression) const noexcept
{
    auto bracketCount = std::unordered_map<char, int>();

    for(const auto &character : expression)
    {
        if(isOpeningParenthesis(character))
            ++bracketCount[character];
        else if(isClosingParenthesis(character))
            --bracketCount[closeParentheses.at(character)];
    }

    for(const auto &pair : bracketCount)
        if(pair.second != 0)
            return pair.second;

    return 0;
}

bool calculator::isOpeningParenthesis(char character) const
{
    return openParentheses.find(character) != openParentheses.end();
}

bool calculator::isClosingParenthesis(char character) const
{
    return closeParentheses.find(character) != closeParentheses.end();
}

bool calculator::hasRelevantTerms(const string &expression) const
{
    return any_of(expression.begin(), expression.end(), [this](const auto &letter)
        {
            if(isDigit(letter) || isAlphabet(letter))
                return true;
        });
}

bool calculator::isDigit(char letter) const
{
    return std::isdigit(letter);
}

bool calculator::isAlphabet(char letter) const
{
    return std::isalpha(letter);
}

bool calculator::isAlgebraicExpression(const string &expression) const
{
    return any_of(expression.begin(), expression.end(), [this](const auto &letter)
        {
            return isAlphabet(letter);
        });
}

void calculator::removeWhitespaces(string &expression) const
{
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
    expression.erase(remove(expression.begin(), expression.end(), '\t'), expression.end());
}

vector<string> calculator::getPostfixTerms(string expression) const
{
    removeWhitespaces(expression);

    vector<string> terms;

    std::stack<stack<char>> bracketLevel;
    bracketLevel.push(stack<char>());

    using sint = string::size_type;

    for(sint i = 0; i < expression.size(); ++i)
    {
        if(isParenthesis(expression[i]))
        {

            const auto braces = expression[i];
            auto &frame = bracketLevel.top();

            if(isOpeningParenthesis(braces))
                bracketLevel.push(stack<char>());
            else if(isClosingParenthesis(braces))
            {
                appendTerms(frame, terms);
                bracketLevel.pop();
            }
        }

        else if(isOperator(expression[i]))
        {
            auto &frame = bracketLevel.top();
            const auto op = expression[i];

            if(operatorPushCondition(frame, op))
                frame.push(op);
            else
            {
                while(operatorPopCondition(frame, op))
                    appendTerms(frame, terms);

                frame.push(op);
            }
        }
        else
        {
            auto length = getOperandLength(expression.begin() + i, expression.end());
            auto operand = expression.substr(i, length);
            terms.push_back(operand);
            i += length - 1;
        }
    }

    auto &frame = bracketLevel.top();

    while(!frame.empty())
    {
        string topOperator{frame.top()};
        frame.pop();

        terms.push_back(topOperator);
    }

    bracketLevel.pop();

    return terms;
}

bool calculator::isOperator(const string &word) const
{
    if(word.size() > 1)
        return false;

    auto firstLetter = word[0];
    return isOperator(firstLetter);
}

bool calculator::isOperator(char letter) const noexcept
{
    return any_of(operators.begin(), operators.end(), [&letter](const auto &op)
        {
            return op == letter;
        }
    );
}

bool calculator::isParenthesis(const string &word) const
{
    if(word.size() > 1)
        return false;

    auto firstLetter = word[0];
    return isParenthesis(firstLetter);
}

bool calculator::isParenthesis(char letter) const noexcept
{
    return openParentheses.find(letter) != openParentheses.end() ||
        closeParentheses.find(letter) != closeParentheses.end();
}

void calculator::appendTerms(stack<char> &frame, vector<string> &terms) const
{
    while(!frame.empty())
    {
        string topOperator{frame.top()};
        frame.pop();
        terms.push_back(topOperator);
    }
}

bool calculator::operatorPushCondition(const stack<char> &frame, char op) const
{
    return
        frame.empty() ||
        getPrecedence(op) > getPrecedence(frame.top()) ||
        (equalPrecedence(op, frame.top()) && isRightAssociative(op));
}

bool calculator::operatorPopCondition(const stack<char> &frame, char op) const
{
    return
        !frame.empty() &&
        getPrecedence(op) <= getPrecedence(frame.top());
}

long long calculator::getOperandLength(string::const_iterator begin, string::const_iterator end) const
{
    auto operandItEnd = find_if(begin, end, [this](const auto &letter)
        {
            return isOperator(letter) || isParenthesis(letter);
        }
    );
    return std::distance(begin, operandItEnd);
}

constexpr int calculator::getPrecedence(char op) const noexcept
{
    if(op == '^')
        return 3;

    if(op == '*' || op == '/' || op == '%')
        return 2;

    if(op == '+' || op == '-')
        return 1;

    return -1;
}

constexpr bool calculator::equalPrecedence(char op1, char op2) const noexcept
{
    return getPrecedence(op1) == getPrecedence(op2);
}

constexpr char calculator::isRightAssociative(char op) const noexcept
{
    if(op == '^')
        return true;

    return false;
}

long long calculator::evaluateOperator(long long leftOperand, char op, long long rightOperand) const
{
    auto result = 0ll;

    switch(op)
    {
        case '^':
            result = power(leftOperand, rightOperand);
            break;

        case '+':
            result = leftOperand + rightOperand;
            break;

        case '-':
            result = leftOperand - rightOperand;
            break;

        case '*':
            result = leftOperand * rightOperand;
            break;

        case '/':
            result = leftOperand / rightOperand;
            break;

        case '%':
            result = leftOperand % rightOperand;
            break;

        default:
            throw runtime_error("Symbol not in operator list");
    }

    return result;
}

long long calculator::power(long long left, long long right) const
{
    if(right < 0)
        throw runtime_error("Negative exponential not allowed for integer types");

    if(right == 0)
        return 1;

    if(right == 1)
        return left;

    auto root = power(left, right / 2);

    if(right % 2 == 0)
        return root * root;
    else
        return root * root * left;
}

long long calculator::stringToLongLong(string number) const
{
    return std::stoll(number);
}

string calculator::getPostfix(const string &expression) const
{
    checkExpression(expression);

    auto tokens = getPostfixTerms(expression);
    string postfix;

    for(auto token : tokens)
    {
        if(isOperator(token))
            postfix += token;
        else
            postfix += enclose(token);
    }

    return postfix;
}

string calculator::enclose(const string &operand) const
{
    return leftEnclosure + operand + rightEnclosure;
}
