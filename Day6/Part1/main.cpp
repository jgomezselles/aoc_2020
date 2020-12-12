#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <set>

size_t count_unique(std::string answers)
{
    answers.erase(std::remove_if(answers.begin(), answers.end(), ::isspace), answers.end());

    std::set<char> unique_answers;
    for(char const& c : answers)
    {
        unique_answers.insert(c);
    }
    return unique_answers.size();
}

size_t sum_different_answers()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string line;
    size_t sum{0};
    std::string buff;
    while (std::getline(input, line))
    {
        buff += " ";
        buff += line;
        if (!line.size())
        {
            sum += count_unique(buff);
            buff.clear();
        }
    }

    buff += " ";
    buff += line;
    sum += count_unique(buff);
    buff.clear();

    input.close();

    return sum;
}

int main()
{
    auto result = sum_different_answers();
    std::cout << "Sum is " << result << "." << std::endl;
    return 0;
}