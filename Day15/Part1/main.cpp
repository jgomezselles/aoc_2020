#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<size_t> numbers{0, 6, 1, 7, 2, 19, 20};

    for (size_t i = numbers.size(); i < 2020; i++)
    {
        const auto it = std::find(numbers.rbegin() + 1, numbers.rend(), numbers.back());
        if (it == numbers.rend())
        {
            numbers.push_back(0);
        }
        else
        {
            numbers.push_back(std::distance(numbers.rbegin(), it));
        }
    }

    std::cout << "2020th is " << numbers.back() << std::endl;

    return 0;
}