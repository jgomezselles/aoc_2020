#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <tuple>

using position = std::tuple<int, int, int, int>;
using mesh = std::set<position>;

mesh parse_input()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    mesh m;
    std::string line;
    int y{0};
    while (std::getline(input, line))
    {
        for (int x = 0; x < line.size(); x++)
        {
            if (line.at(x) == '#')
            {
                m.insert({x, y, 0, 0});
            }
        }
        ++y;
    }
    input.close();

    return m;
}

std::vector<position> get_neighbors(const position &p)
{
    std::vector<position> neighs;
    neighs.reserve(81);

    const auto &[x, y, z, w] = p;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            for (int k = z - 1; k <= z + 1; k++)
            {
                for (int l = w - 1; l <= w + 1; l++)
                {
                    neighs.push_back({i, j, k, l});
                }
            }
        }
    }
    return neighs;
}

char get_next_state(const position &p, const mesh &prev)
{
    size_t active_neighbors{0};
    bool was_active{false};
    for (const auto &neigh : get_neighbors(p))
    {
        const bool found = prev.find(neigh) != prev.end();
        if (p == neigh)
        {
            was_active = found;
            continue;
        }
        active_neighbors += found;
    }

    return was_active ? (active_neighbors == 2 || active_neighbors == 3) : (active_neighbors == 3);
}

void update_mesh(mesh &prev)
{
    mesh next;
    for (const auto &p : prev)
    {
        for (const auto &new_pos : get_neighbors(p))
        {
            if (get_next_state(new_pos, prev))
            {
                next.insert(new_pos);
            }
        }
    }
    prev = next;
    return;
}

int main()
{
    auto m = parse_input();
    for (size_t i = 1; i <= 6; i++)
    {
        update_mesh(m);
        std::cout << "Active cube count after cycle " << i << " is " << m.size() << std::endl;
    }

    return 0;
}