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

void calculate(std::vector<int> &numbers)
{
    for (const auto &i : numbers)
    {
        for (const auto &j : numbers)
        {
            if (i == j)
            {
                continue;
            }
            for (const auto &k : numbers)
            {
                if (k == j || k == i)
                {
                    continue;
                }
                if (i + j + k == 2020)
                {
                    std::cout << "Result = " << i << " * " << j << " * " << k << " = " << i * j * k << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "You won't find it here" << std::endl;
}

int main()
{
    auto numbers = get_input();

    std::cout << "Got " << numbers.size() << " numbers." << std::endl;

    std::sort(numbers.begin(), numbers.end());

    calculate(numbers);

    return 0;
}