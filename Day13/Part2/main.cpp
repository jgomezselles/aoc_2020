#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

std::map<size_t, size_t> read_notes()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string tmp;
    std::getline(input, tmp);
    std::getline(input, tmp);
    input.close();

    std::stringstream ss(tmp);
    std::map<size_t, size_t> pos_id;
    size_t position{0};
    while (std::getline(ss, tmp, ','))
    {
        if (tmp != "x")
        {
            pos_id.emplace(position, atoi(tmp.c_str()));
        }
        ++position;
    }
    return pos_id;
}

size_t result(const std::map<size_t, size_t> &pos_id)
{
    size_t timestamp{1};
    size_t step{1};
    for (const auto &[pos, id] : pos_id)
    {
        bool found{false};
        while (!found)
        {
            if ((timestamp + pos) % id != 0)
            {
                timestamp += step;
            }
            else
            {
                found = true;
            }
        }
        //Here is the trick. As they're all prime numbers, once a combination
        //is valid for a given number of ids, the next valid one needs to, at least
        //be another multiple of those prime numbers.
        step *= id;
    }

    return timestamp;
}

int main()
{
    std::cout << "Result is: " << result(read_notes()) << std::endl;
    return 0;
}