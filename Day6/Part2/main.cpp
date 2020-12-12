#include <iostream>
#include <fstream>
#include <set>

bool found_in_all(const char &to_find, const std::set<std::string> &answers)
{
    bool found{true};
    for (const auto &ans : answers)
    {
        if (found = ans.find(to_find) != std::string::npos; !found)
        {
            break;
        }
    }
    return found;
}

size_t count_repeated(const std::set<std::string> &answers)
{
    size_t unique_answers{0};
    for (char const &char_in_first : *answers.begin())
    {
        unique_answers +=  found_in_all(char_in_first, answers);
    }
    return unique_answers;
}

size_t sum_repeated_answers()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string line;
    size_t sum{0};
    std::set<std::string> group_answers;
    while (std::getline(input, line))
    {
        if (line.size())
        {
            group_answers.insert(line);
        }
        else
        {
            sum += count_repeated(group_answers);
            group_answers.clear();
        }
    }

    if (line.size())
    {
        group_answers.insert(line);
    }
    sum += count_repeated(group_answers);

    input.close();

    return sum;
}

int main()
{
    auto result = sum_repeated_answers();
    std::cout << "Sum is " << result << "." << std::endl;
    return 0;
}