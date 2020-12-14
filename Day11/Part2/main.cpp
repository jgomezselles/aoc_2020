#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>

std::vector<std::string> load_seats()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string line;
    std::vector<std::string> seats;
    while (std::getline(input, line))
    {
        seats.push_back(line);
    }
    input.close();

    return seats;
}

char west(const std::vector<std::string> &seats, const size_t i, size_t j)
{
    while (j > 0)
    {
        --j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char north_west(const std::vector<std::string> &seats, size_t i, size_t j)
{
    while (i > 0 && j > 0)
    {
        --i;
        --j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char north(const std::vector<std::string> &seats, size_t i, const size_t j)
{
    while (i > 0)
    {
        --i;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char north_east(const std::vector<std::string> &seats, size_t i, size_t j)
{
    while (i > 0 && j < seats.at(i).size() - 1)
    {
        --i;
        ++j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char east(const std::vector<std::string> &seats, const size_t i, size_t j)
{
    while (j < seats.at(i).size() - 1)
    {
        ++j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char south_east(const std::vector<std::string> &seats, size_t i, size_t j)
{
    while (i < seats.size() - 1 && j < seats.at(i).size() - 1)
    {
        ++i;
        ++j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char south(const std::vector<std::string> &seats, size_t i, const size_t j)
{
    while (i < seats.size() - 1)
    {
        ++i;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

char south_west(const std::vector<std::string> &seats, size_t i, size_t j)
{
    while (i < seats.size() - 1 && j > 0)
    {
        ++i;
        --j;
        const auto c = seats.at(i).at(j);
        if (c == 'L' || c == '#')
        {
            return c;
        }
    }
    return '.';
}

std::pair<char, bool> get_new_state(const std::vector<std::string> &seats, const size_t i, const size_t j)
{
    auto &prev_state = seats.at(i).at(j);
    if (prev_state == '.')
    {
        return {prev_state, false};
    }

    std::string in_sight{
        west(seats, i, j),
        north_west(seats, i, j),
        north(seats, i, j),
        north_east(seats, i, j),
        east(seats, i, j),
        south_east(seats, i, j),
        south(seats, i, j),
        south_west(seats, i, j)};

    size_t occupied{0};

    for (char const c : in_sight)
    {
        occupied += c == '#';
    }

    switch (prev_state)
    {
    case 'L':
        return occupied > 0 ? std::make_pair(prev_state, false) : std::make_pair('#', true);
    case '#':
        return occupied < 5 ? std::make_pair(prev_state, false) : std::make_pair('L', true);
    default:
        std::cout << "We shouldn't be here" << std::endl;
        return {};
    }
}

void print_seats(const std::vector<std::string> &seats)
{
    std::cout << "Printing seats" << std::endl;
    for (const auto &row : seats)
    {
        std::cout << row << std::endl;
    }
}

size_t transform(std::vector<std::string> &seats, size_t &steps)
{
    ++steps;
    std::vector<std::string> new_state;
    size_t transforms{0};
    for (size_t i = 0; i < seats.size(); i++)
    {
        const auto &row = seats.at(i);
        std::string new_row;
        for (size_t j = 0; j < row.size(); j++)
        {
            const auto [st, transformed] = get_new_state(seats, i, j);
            new_row += st;
            transforms += transformed;
        }
        new_state.push_back(new_row);
    }

    seats = new_state;
    return transforms == 0 ? steps : transform(seats, steps);
}

size_t count_ocupied(const std::vector<std::string> &seats)
{
    size_t occupied{0};
    for (const auto &row : seats)
    {
        for (char const c : row)
        {
            occupied += c == '#';
        }
    }
    return occupied;
}

int main()
{
    auto seats = load_seats();
    size_t steps{0};
    auto n_steps = transform(seats, steps);
    std::cout << "All stable after " << n_steps << " steps." << std::endl;
    const auto occupied = count_ocupied(seats);
    std::cout << "Occupied: " << occupied << " seats." << std::endl;
    return 0;
}