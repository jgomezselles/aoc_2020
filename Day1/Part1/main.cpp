#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <optional>

std::vector<int> get_input()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::vector<int> numbers;
    std::string line;
    while (std::getline(input, line))
    {
        if (!line.size())
        {
            continue;
        }

        numbers.push_back(atoi(line.c_str()));
    }

    input.close();

    return numbers;
}

bool calculate(std::vector<int> &numbers)
{
    int max = numbers.at(numbers.size() - 1);
    int min = numbers.at(0);
    while (min != max)
    {
        int sum = max + min;
        if (sum > 2020)
        {
            numbers.pop_back();
            max = numbers.at(numbers.size() - 1);
        }
        else if (sum < 2020)
        {
            numbers.erase(numbers.begin());
            min = numbers.at(0);
        }
        else
        {
            std::cout << "Result = " << min << " * " << max << " = " << min * max << std::endl;
            return true;
        }
    }
    std::cout << "You won't find it here" << std::endl;
    return true;
}

int main()
{
    auto numbers = get_input();

    std::cout << "Got " << numbers.size() << " numbers." << std::endl;

    std::sort(numbers.begin(), numbers.end());

    if (calculate(numbers))
    {
        return 1;
    }

    return 0;
}