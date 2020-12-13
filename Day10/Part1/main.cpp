#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

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

std::pair<size_t, size_t> get_differences(const std::set<size_t> &adapters)
{
    size_t one_jolt_diffs{0}, three_jolt_diffs{0};
    for (auto it = std::next(adapters.begin()); it != adapters.end(); ++it)
    {
        const auto diff = *it - *std::prev(it);
        switch (diff)
        {
        case 1:
            ++one_jolt_diffs;
            break;
        case 3:
            ++three_jolt_diffs;
            break;
        default:
            std::cout << "Found other diff: " << diff << " between " << *it << " and " << *std::prev(it) << std::endl;
            break;
        }
    }
    return {one_jolt_diffs, three_jolt_diffs};
}

int main()
{
    const auto adapters = get_ordered_adapters();
    const auto [ones, threes] = get_differences(adapters);
    std::cout << "Result is: delta_1Js -> " << ones << " delta_3Js -> " << threes << std::endl;
    std::cout << "Result is: " << ones * threes << std::endl;

    return 0;
}