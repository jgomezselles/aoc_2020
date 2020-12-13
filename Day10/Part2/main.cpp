#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <map>

std::set<size_t> get_ordered_adapters()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string line;
    std::set<size_t> adapters;
    while (std::getline(input, line))
    {
        adapters.insert(stoull(line));
    }

    adapters.insert(0);
    adapters.insert(3 + *adapters.rbegin());

    input.close();

    return adapters;
}

std::vector<size_t> get_consecutives(const std::set<size_t> &adapters)
{
    std::vector<size_t> cont_ones;
    size_t partial{0};
    for (auto it = std::next(adapters.begin()); it != adapters.end(); ++it)
    {
        if (*it - *std::prev(it) == 1)
        {
            ++partial;
        }
        else if (partial != 0)
        {
            cont_ones.push_back(partial);
            partial = 0;
        }
    }
    return cont_ones;
}

//Shame on me, I wanted to have a formula for this
//but couldn't make it, so I calculated these by hand.
std::map<size_t, size_t> partial_combinations{
    {1, 1}, // If you have only 2 consecutive numbers (one diff==1), you only have one choice: to keep it.
    {2, 2}, // If you have 3 consecutive numbers (2 diffs==1), you only have two choices: keep the middle one, or remove it
    {3, 4}, // And so on...
    {4, 7}};

size_t get_combinations(const std::vector<size_t> &diffs)
{
    size_t sum{1};
    for (const auto &d : diffs)
    {
        sum *= partial_combinations.at(d);
    }
    return sum;
}

int main()
{
    const auto c = get_combinations(get_consecutives(get_ordered_adapters()));
    std::cout << "Result is: " << c;

    return 0;
}