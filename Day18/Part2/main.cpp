#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <map>

//Implementation of http://csis.pace.edu/~murthy/ProgrammingProblems/16_Evaluation_of_infix_expressions
size_t compute(const size_t val1, const size_t val2, char const op)
{
    switch (op)
    {
    case '+':
        return val1 + val2;
        break;
    case '*':
        return val1 * val2;
        break;
    default:
        break;
    }

    std::cout << "Error!" << std::endl;
    return 0;
}

void process(std::stack<char> &operators, std::stack<size_t> &operands)
{
    auto val1 = operands.top();
    operands.pop();
    auto op = operators.top();
    operators.pop();
    auto val2 = operands.top();
    operands.pop();
    operands.push(compute(val1, val2, op));
}

std::map<char, size_t> precedence{
    {'+', 0},
    {'*', 1}};

size_t process_expression(const std::string &exp)
{
    std::stack<size_t> operands;
    std::stack<char> operators;

    for (const char &c : exp)
    {
        if (std::isspace(c))
        {
            continue;
        }

        if (std::isdigit(c))
        {
            std::string a{c};
            operands.push(atoi(a.c_str()));
            continue;
        }

        if (c == '+' || c == '*')
        {
            if(operators.empty() || operators.top() == '(' || precedence.at(c) < precedence.at(operators.top()))
            {
                operators.push(c);
                continue;
            }
        }

        if (c == '(')
        {
            operators.push(c);
            continue;
        }

        if (c == ')')
        {
            while (operators.top() != '(')
            {
                process(operators, operands);
            }

            operators.pop();
            continue;
        }

        process(operators, operands);
        operators.push(c);
    }

    while (operators.size())
    {
        process(operators, operands);
    }

    return operands.top();
}

int main()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open input.txt" << std::endl;
        return {};
    }

    size_t res{0};
    std::string line;
    while (std::getline(input, line))
    {
        res += process_expression(line);
    }

    std::cout << "Result is " << res << std::endl;

    return 0;
}