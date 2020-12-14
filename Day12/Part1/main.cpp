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

class ship
{
public:
    ship(){};

    void execute(const char c, const float n)
    {
        switch (c)
        {
        case 'N':
            return north(n);
            break;
        case 'S':
            return south(n);
            break;
        case 'E':
            return east(n);
            break;
        case 'W':
            return west(n);
            break;
        case 'L':
            return rotate(n);
            break;
        case 'R':
            return rotate(-n);
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
        x += n * std::cos(deg * pi / 180.0);
        y += n * std::sin(deg * pi / 180.0);
    };

    void rotate(const float &n)
    {
        deg += n;
    };

    void move(const float &dx, const float &dy)
    {
        x += dx;
        y += dy;
    };

    void north(const float &n) { move(0, n); };
    void east(const float &n) { move(n, 0); };
    void south(const float &n) { move(0, -n); };
    void west(const float &n) { move(-n, 0); };

    float x = 0;
    float y = 0;
    float deg = 0;
};

int main()
{
    auto instructions = load_instructions();
    ship s;
    for (const auto &[i, n] : instructions)
    {
        s.execute(i, n);
        const auto &[x, y] = s.get_position();
    }

    const auto &[x, y] = s.get_position();
    std::cout << "Distance is: " << std::fabs(x) + std::fabs(y) << std::endl;

    return 0;
}