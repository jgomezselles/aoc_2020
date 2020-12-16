#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::vector<size_t> input{0, 6, 1, 7, 2, 19, 20};
    size_t limit{30000000};
    std::size_t result{};

    std::map<size_t, size_t> numbers;
    for (size_t i = 0; i < input.size() - 1; i++)
    {
        numbers.insert_or_assign(input.at(i), i + 1);
    }

    std::size_t next = input.back();
    for (size_t i = numbers.size() + 1; i <= limit; i++)
    {
        size_t to_insert{next};
        const auto it = numbers.find(to_insert);
        next = it == numbers.end() ? 0 : i - it->second;
        numbers.insert_or_assign(to_insert, i);

        if (i == limit)
        {
            result = to_insert;
        }
    }

    std::cout << limit << " is " << result << std::endl;

    return 0;
}