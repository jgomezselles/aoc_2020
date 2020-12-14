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

std::pair<char, bool> get_new_state(const std::vector<std::string> &seats, const size_t i, const size_t j)
{
    const auto &row = seats.at(i);
    auto &prev_state = row.at(j);

    if (prev_state == '.')
    {
        return {prev_state, false};
    }

    size_t occupied{0};

    size_t min_i = i == 0 ? i : i - 1;
    size_t max_i = i == seats.size() - 1 ? i : i + 1;

    for (size_t idx_i = min_i; idx_i <= max_i; idx_i++)
    {
        size_t min_j = j == 0 ? j : j - 1;
        size_t max_j = j == row.size() - 1 ? j : j + 1;

        for (size_t idx_j = min_j; idx_j <= max_j; idx_j++)
        {
            if (!(idx_i == i && idx_j == j))
            {
                occupied += seats.at(idx_i).at(idx_j) == '#';
            }
        }
    }

    switch (prev_state)
    {
    case 'L':
        return occupied > 0 ? std::make_pair(prev_state, false) : std::make_pair('#', true);
    case '#':
        return occupied < 4 ? std::make_pair(prev_state, false) : std::make_pair('L', true);
    default:
        std::cout << "We shouldn't be here" << std::endl;
        return {};
    }
}

void print_seats(const std::vector<std::string> &seats)
{
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