#include <iostream>
#include <fstream>

size_t get_trees()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string line;
    std::getline(input, line);

    size_t trees{0}, x{0};
    while (std::getline(input, line))
    {
        x += 3;
        x %= line.size();
        trees += line[x] == '#';
    }

    input.close();

    return trees;
}

int main()
{
    auto trees = get_trees();
    std::cout << "Number of trees is " << trees << "." << std::endl;
    return 0;
}