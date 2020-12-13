#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <optional>
#include <vector>
#include <algorithm>

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

std::pair<size_t, std::vector<size_t>> get_data()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string line;
    std::deque<size_t> last_25;
    std::vector<size_t> entries;
    std::optional<size_t> weakness;
    while (std::getline(input, line))
    {
        size_t next_n{stoull(line)};
        entries.push_back(next_n);

        if (!weakness)
        {

            if (last_25.size() < 25)
            {
                last_25.push_back(next_n);
                continue;
            }

            if (!validate_entry(next_n, last_25))
            {
                std::cout << next_n << " is not the sum of any of the previous adjacent 25!" << std::endl;
                weakness.emplace(next_n);
            }

            last_25.pop_front();
            last_25.push_back(next_n);
        }
    }

    input.close();

    return {*weakness, entries};
}

std::pair<size_t, size_t> find_range(const size_t weakness, const std::vector<size_t> &entries)
{
    for (auto it1 = entries.begin(); it1 != entries.end() - 1; ++it1)
    {
        auto sum{*it1}, min{*it1}, max{*it1};
        for (auto it2 = it1 + 1; it2 != entries.end(); ++it2)
        {
            max = std::max(*it2, max);
            min = std::min(*it2, min);
            sum += *it2;

            if (sum == weakness)
            {
                return {min, max};
            }

            if (sum > weakness)
            {
                break;
            }
        }
    }

    std::cout << "Could not find the range." << std::endl;
    return {};
}

int main()
{
    const auto [weakness, entries] = get_data();
    const auto [min, max] = find_range(weakness, entries);
    std::cout << "Min is: " << min << " max is: " << max << ". Result is: " << min + max << std::endl;
    return 0;
}
