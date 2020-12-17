#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include <vector>

void add_range(std::map<size_t, size_t> &ranges, const std::string &line)
{
    std::map<size_t, size_t> new_ranges;

    //This is so dirty
    std::stringstream ss(line);
    std::string tmp;
    std::getline(ss, tmp, ':');

    std::getline(ss, tmp, '-');
    size_t range1_min = atoi(tmp.c_str());
    std::getline(ss, tmp, 'o');
    new_ranges.emplace(range1_min, atoi(tmp.c_str()));
    std::getline(ss, tmp, ' ');

    std::getline(ss, tmp, '-');
    size_t range2_min = atoi(tmp.c_str());
    std::getline(ss, tmp);
    new_ranges.emplace(range2_min, atoi(tmp.c_str()));

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
    std::map<size_t, size_t> ranges;
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
            add_range(ranges, line);
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

    size_t error_rate{0};
    for (const auto &ticket : nearby_tickets)
    {
        for (const auto number : ticket)
        {
            error_rate += number * (!is_valid(number, ranges));
        }
    }

    std::cout << "Error rate is: " << error_rate << std::endl;

    return;
}

int main()
{
    parse_input();
    return 0;
}