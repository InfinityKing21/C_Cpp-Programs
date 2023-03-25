#include<string>
#include<vector>
#include<unordered_map>
#include<stack>

class calculator
{
public:

    calculator();

    // Segregates operands when getting expression in Postfix
    std::string leftEnclosure, rightEnclosure;

    long long getResult(std::string expression) const;
    std::string getPostfix(const std::string &expression) const;

private:
    std::vector<char> operators;
    std::unordered_map<char, char> openParentheses, closeParentheses;

    void checkExpression(const std::string &expression) const;
    long long countMatchingParenthesis(const std::string &expression) const noexcept;
    bool hasRelevantTerms(const std::string &expression) const;

    bool isDigit(char letter) const;
    bool isAlphabet(char letter) const;
    bool isAlgebraicExpression(const std::string &expression) const;

    void removeWhitespaces(std::string &expression) const;

    std::vector<std::string> getPostfixTerms(std::string expression) const;

    bool isOperator(const std::string &word) const;
    bool isOperator(char letter) const noexcept;

    bool isParenthesis(const std::string &word) const;
    bool isParenthesis(char letter) const noexcept;

    bool isOpeningParenthesis(char letter) const;
    bool isClosingParenthesis(char letter) const;

    void appendTerms(std::stack<char> &frame, std::vector<std::string> &terms) const;

    bool operatorPushCondition(const std::stack<char> &frame, char op) const;
    bool operatorPopCondition(const std::stack<char> &frame, char op) const;

    long long getOperandLength(std::string::const_iterator begin, std::string::const_iterator end) const;

    constexpr int getPrecedence(char op) const noexcept;
    constexpr bool equalPrecedence(char op1, char op2) const noexcept;

    constexpr char isRightAssociative(char op) const noexcept;

    long long evaluateOperator(long long leftOperand, char op, long long rightOperand) const;

    long long power(long long left, long long right) const;
    long long stringToLongLong(std::string number) const;


    std::string enclose(const std::string &operand) const;
    constexpr char getLeftEnclosure() const noexcept;
    constexpr char getRightEnclosure() const noexcept;
};
