#include <iostream>
#include <fstream>
#include <vector>

struct slope
{
    size_t delta_x;
    size_t delta_y;
    size_t current_x;
    size_t trees;
};

bool is_tree(slope &sl, const std::string &line)
{
    sl.current_x += sl.delta_x;
    sl.current_x %= line.size();
    return line[sl.current_x] == '#';
}

void compute_trees(std::vector<slope>& slopes)
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return;
    }
    std::string line;
    std::getline(input, line);

    size_t y{1};
    while (std::getline(input, line))
    {
        for (auto &sl : slopes)
        {
            if(!(y % sl.delta_y))
            {
                sl.trees += is_tree(sl, line);
            }
        }
        ++y;
    }

    input.close();
    return;
}

int main()
{
    
    std::vector<slope> slopes
    {
        {1, 1, 0, 0},
        {3, 1, 0, 0},
        {5, 1, 0, 0},
        {7, 1, 0, 0},
        {1, 2, 0, 0}
    };

    compute_trees(slopes);
    
    long long int mult{1};
    for (const auto &sl : slopes)
    {
        mult *= (long long int)sl.trees;
    }
    std::cout << "Number wanted is " << mult << "." << std::endl;
    return 0;
}