#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

void add_range(std::map<size_t, size_t> &ranges, const std::string &line,
               std::map<std::string, std::map<size_t, size_t>> &named_ranges)
{
    std::map<size_t, size_t> new_ranges;

    std::stringstream ss(line);
    std::string tmp;
    std::getline(ss, tmp, ':');
    std::string name = tmp;
    std::getline(ss, tmp, '-');
    size_t range1_min = atoi(tmp.c_str());
    std::getline(ss, tmp, 'o');
    new_ranges.emplace(range1_min, atoi(tmp.c_str()));
    std::getline(ss, tmp, ' ');

    std::getline(ss, tmp, '-');
    size_t range2_min = atoi(tmp.c_str());
    std::getline(ss, tmp);
    new_ranges.emplace(range2_min, atoi(tmp.c_str()));

    named_ranges[name] = new_ranges;

    for (const auto &[min, max] : new_ranges)
    {
        size_t m{min}, M{max};
        std::set<size_t> intersections;
        for (const auto &[r_min, r_max] : ranges)
        {
            if ((min >= r_min && min <= r_max) || (max >= r_min && max <= r_max) ||
                (min <= r_min && max >= r_max))
            {
                intersections.insert(r_min);
                M = std::max(M, r_max);
                m = std::min(m, r_min);
            }
        }

        for (const auto &i : intersections)
        {
            ranges.erase(i);
        }

        ranges.emplace(m, M);
    }
}

bool is_valid(const size_t number, const std::map<size_t, size_t> ranges)
{
    for (const auto &[min, max] : ranges)
    {
        if (number >= min && number <= max)
        {
            return true;
        }
    }
    return false;
}

std::vector<size_t> scan_ticket(const std::string &line)
{
    std::stringstream ss(line);
    std::string field;
    std::vector<size_t> ticket;
    while (std::getline(ss, field, ','))
    {
        ticket.push_back(atoi(field.c_str()));
    }

    return ticket;
}

void erase_field(std::map<size_t, std::set<std::string>> &possible_positions, size_t pos, const std::string name)
{
    possible_positions.at(pos).erase(name);

    if (possible_positions.at(pos).size() != 1)
    {
        return;
    }

    const std::string name_to_propagate = *possible_positions.at(pos).begin();
    for (auto &[other, names] : possible_positions)
    {
        if (names.size() != 1)
        {
            erase_field(possible_positions, other, name_to_propagate);
        }
    }
}

void parse_input()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return;
    }

    size_t line_number{0};
    std::string line;
    std::map<size_t, size_t> total_ranges;
    std::map<std::string, std::map<size_t, size_t>> named_ranges;

    std::vector<size_t> my_ticket;
    std::vector<std::vector<size_t>> nearby_tickets;

    while (std::getline(input, line))
    {
        ++line_number;
        if (!line.size())
        {
            continue;
        }

        if (line_number <= 20)
        {
            add_range(total_ranges, line, named_ranges);
            continue;
        }

        if (line_number == 23)
        {
            my_ticket = scan_ticket(line);
            continue;
        }

        if (line_number >= 26)
        {
            nearby_tickets.push_back(scan_ticket(line));
            continue;
        }
    }

    input.close();

    std::map<size_t, std::set<std::string>> possible_positions;
    std::set<std::string> field_names;
    for (const auto &[n, _] : named_ranges)
    {
        field_names.insert(n);
    }

    for (size_t i = 0; i < my_ticket.size(); i++)
    {
        possible_positions.emplace(i, field_names);
    }

    for (const auto &ticket : nearby_tickets)
    {
        bool is_valid_ticket{true};
        for (const auto number : ticket)
        {
            if (!is_valid(number, total_ranges))
            {
                is_valid_ticket = false;
                break;
            }
        }

        if (!is_valid_ticket)
        {
            continue;
        }

        for (size_t i = 0; i < ticket.size(); i++)
        {
            for (const auto &[name, range] : named_ranges)
            {
                if (!is_valid(ticket.at(i), range))
                {
                    erase_field(possible_positions, i, name);
                }
            }
        }
    }

    size_t result{1};
    for(size_t i = 0; i < my_ticket.size(); i++)
    {
        std::string name = *possible_positions.at(i).begin();
        if(name.find("departure") == std::string::npos)
        {
            continue;
        }
        result *= my_ticket.at(i);
    }

    std::cout << "Results is: " << result << std::endl;

    return;
}

int main()
{
    parse_input();
    return 0;
}