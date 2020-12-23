#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <map>
#include <deque>

//This is a small rework of https://github.com/AshKelly/advent-of-code-2020/blob/main/day19/solution.cpp
//Check it out! The algorithm is not mine!
//The blog is pretty cool! :) https://www.ashkelly.co.uk/blog/aoc20d19/
/*
    Differences:
        Maps are used because elements are not to be repeated.
        Deque insted of list because we don't want to do things in the middle of the container.
        Some C++17 stuff for if statements.
        idx used in function check to avoid copying strings around.
        Pattern preparation with stringstream and nested whiles.
        Some const references added to avoid copying things when not needed.

    In any case, I was stuck with this one until I found AshKelly's solution because I spent a lot
    of time trying to store a map of functions, and that killed me, so AshKelly's idea was very similar
    to what I wanted (not a regex fan) but I miserably failed :( .
*/

std::map<size_t, char> base_patterns;
std::map<size_t, std::vector<std::deque<size_t>>> patterns;

bool check(const std::string &message, const size_t idx, std::deque<size_t> &sequence)
{
    if (idx >= message.size() || sequence.empty())
    {
        return idx >= message.size() && sequence.empty();
    }

    if (sequence.size() > message.size())
    {
        return false;
    }

    if (const auto &it1 = base_patterns.find(sequence.front()); it1 != base_patterns.end())
    {
        sequence.pop_front();
        return (*it1).second == message.at(idx) ? check(message, idx + 1, sequence) : false;
    }

    auto front = sequence.front();
    sequence.pop_front();
    for (auto t : patterns.at(front))
    {
        t.insert(t.end(), sequence.begin(), sequence.end());
        if (check(message, idx, t))
        {
            return true;
        }
    }

    return false;
}

void add_pattern(const std::string &line)
{
    std::stringstream ss(line);
    std::string tmp;
    std::getline(ss, tmp, ':');
    size_t idx = stoul(tmp);

    std::vector<std::deque<size_t>> these_patterns;
    while (std::getline(ss, tmp, '|'))
    {
        std::stringstream ss2(tmp);
        std::string tmp2;

        std::deque<size_t> pattern;
        while (std::getline(ss2, tmp2, ' '))
        {
            if (tmp2.empty())
            {
                continue;
            }
            pattern.push_back(stoul(tmp2));
        }
        these_patterns.push_back(pattern);
    }

    patterns.emplace(idx, these_patterns);
}

int main()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open input.txt" << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            break;
        }

        if (line.find('"') != line.npos)
        {
            base_patterns.emplace(stoul(line.substr(0, line.find(':'))), line.at(line.find('"') + 1));
        }
        else
        {
            add_pattern(line);
        }
    }

    std::vector<std::string> messages;
    while (std::getline(input, line))
    {
        messages.push_back(line);
    }

    input.close();

    size_t ans{0};

    // Part 1
    for (const auto &message : messages)
    {
        std::deque<size_t> sequence{0};
        ans += check(message, 0, sequence);
    }
    std::cout << "Answer 1: " << ans << std::endl;

    // Part 2
    patterns[8] = {{42}, {42, 8}};
    patterns[11] = {{42, 31}, {42, 11, 31}};

    ans = 0;
    for (const auto &message : messages)
    {
        std::deque<size_t> sequence{0};
        ans += check(message, 0, sequence);
    }

    std::cout << "Answer 2: " << ans << std::endl;

    return 0;
}