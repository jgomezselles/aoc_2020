#include <iostream>
#include <fstream>
#include <set>
#include <cctype>
#include <algorithm>
#include <math.h>

void compute_seat()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return;
    }

    std::string line;
    int max{0};
    std::set<unsigned> ids;
    while (std::getline(input, line))
    {
        if (!line.size())
        {
            continue;
        }

        unsigned row{0}, column{0};

        for (size_t i = 0; i <= 9; i++)
        {
            const auto c = line.at(i);
            switch (c)
            {
            case 'B':
                row += pow(2, 6 - i);
                break;
            case 'R':
                column += pow(2, 9 - i);
                break;
            default:
                break;
            }
        }

        unsigned result = row * 8 + column;

        if (max < result)
        {
            max = result;
        }
        ids.insert(result);
    }

    input.close();
    std::cout << "Max: " << max << std::endl;
    for (unsigned i = 1; i < max; i++)
    {
        if (ids.find(i) == ids.end() &&
            ids.find(i + 1) != ids.end() &&
            ids.find(i - 1) != ids.end())
        {
            std::cout << "My seat is: " << i << std::endl;
        }
    }

    return;
}

int main()
{
    compute_seat();
    return 0;
}