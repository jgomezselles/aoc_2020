#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

const float pi = std::acos(-1);

std::vector<std::pair<char, size_t>> load_instructions()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string line;
    std::vector<std::pair<char, size_t>> instructions;
    while (std::getline(input, line))
    {
        instructions.push_back({line.at(0), atoi(line.substr(1).c_str())});
    }

    input.close();

    return instructions;
}

class waypoint
{
public:
    waypoint(){};

    void r_rotate(const float &deg)
    {
        auto rads = deg * pi / 180.0;
        auto cos = std::cos(rads);
        auto sin = std::sin(rads);
        auto x_tmp = x * cos + y * sin;

        y = -x * sin + y * cos;
        x = x_tmp;
    };

    void l_rotate(const float &deg)
    {
        auto rads = deg * pi / 180.0;
        auto cos = std::cos(rads);
        auto sin = std::sin(rads);
        auto x_tmp = x * cos - y * sin;

        y = x * sin + y * cos;
        x = x_tmp;
    };

    void north(const float &n) { move(0, n); };
    void east(const float &n) { move(n, 0); };
    void south(const float &n) { move(0, -n); };
    void west(const float &n) { move(-n, 0); };

    float x = 10;
    float y = 1;

private:
    void move(const float &dx, const float &dy)
    {
        x += dx;
        y += dy;
    };
};

class ship
{
public:
    ship() : w(){};

    void execute(const char c, const float n)
    {
        switch (c)
        {
        case 'N':
            return w.north(n);
            break;
        case 'S':
            return w.south(n);
            break;
        case 'E':
            return w.east(n);
            break;
        case 'W':
            return w.west(n);
            break;
        case 'L':
            return w.l_rotate(n);
            break;
        case 'R':
            return w.r_rotate(n);
            break;
        case 'F':
            return move_forward(n);
            break;
        default:
            break;
        }
    };

    std::pair<float, float> get_position() { return {x, y}; };

private:
    void move_forward(const size_t &n)
    {
        x += w.x * n;
        y += w.y * n;
    };

    float x = 0;
    float y = 0;
    waypoint w;
};

int main()
{
    ship s;
    for (const auto &[i, n] : load_instructions())
    {
        s.execute(i, n);
    }

    const auto &[x, y] = s.get_position();
    std::cout << "Distance is: " << std::fabs(x) + std::fabs(y) << std::endl;
    return 0;
}