#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>

bool validate_entry(const size_t entry, const std::deque<size_t> &last_25)
{
    for (auto it1 = last_25.begin(); it1 != last_25.end() - 1; ++it1)
    {
        for (auto it2 = it1 + 1; it2 != last_25.end(); ++it2)
        {
            if (*it1 != *it2 && *it1 + *it2 == entry)
            {
                return true;
            }
        }
    }
    return false;
}

void get_first_wrong()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return;
    }

    std::string line;
    std::deque<size_t> last_25;
    while (std::getline(input, line))
    {
        size_t next_n{stoull(line)};
        if (last_25.size() < 25)
        {
            last_25.push_back(next_n);
            continue;
        }

        if (!validate_entry(next_n, last_25))
        {
            std::cout << next_n << " is not the sum of any of the previous adjacent 25!" << std::endl;
            break;
        }

        last_25.pop_front();
        last_25.push_back(next_n);
    }

    input.close();

    return;
}

int main()
{
    get_first_wrong();
    return 0;
}