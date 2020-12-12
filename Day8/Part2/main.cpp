#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <limits>

enum class action
{
    NOP = 0,
    JUMP = 1,
    ACC = 2
};

static const std::map<std::string, action> str_to_action{
    {"nop", action::NOP},
    {"jmp", action::JUMP},
    {"acc", action::ACC}};

struct state
{
    size_t pos{0};
    int accum{0};
    std::set<size_t> actions_executed{};
};

std::vector<std::pair<action, int>> actions;

std::pair<action, int> get_action(const std::string &line)
{
    std::stringstream ss(line);
    std::string tmp;
    action a;
    int n;
    bool first{true};
    while (std::getline(ss, tmp, ' '))
    {
        if (first)
        {
            a = str_to_action.at(tmp);
            first = false;
        }
        else
        {
            n = atoi(tmp.c_str());
        }
    }
    return {a, n};
}

std::vector<std::pair<action, int>> read_actions()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(input, line))
    {
        actions.push_back(get_action(line));
    }
    input.close();

    return actions;
}

void exec_action(state &st, const std::vector<std::pair<action, int>>& action_set)
{
    const auto &[a, n] = action_set.at(st.pos);

    switch (a)
    {
    case action::NOP:
        st.pos += 1;
        break;
    case action::ACC:
        st.pos += 1;
        st.accum += n;
        break;
    case action::JUMP:
        st.pos += n;
        break;
    default:
        std::cout << "Action not recognized!" << std::endl;
        break;
    }
}

bool exec_actions(const std::vector<std::pair<action, int>> &actions_to_try)
{
    if(actions_to_try.empty())
    {
        return true;
    }

    state st;
    while (st.pos < actions_to_try.size())
    {
        if (const auto [_, is_new] = st.actions_executed.insert(st.pos); !is_new)
        {
            return false;
        }
        exec_action(st, actions_to_try);
    }

    std::cout << "This is the one!" << std::endl;
    std::cout << "Accum " << st.accum << std::endl;
    return true;
}

std::vector<std::pair<action, int>> get_next_try(size_t &last_tried)
{
    auto next_set = actions;
    for (size_t pos = last_tried + 1; pos < next_set.size(); pos++)
    {
        auto &[a, _] = next_set.at(pos);
        switch (a)
        {
        case action::JUMP:
            a = action::NOP;
            last_tried = pos;
            return next_set;
            break;
        case action::NOP:
            a = action::JUMP;
            last_tried = pos;
            return next_set;
            break;
        default:
            break;
        }
    }
    std::cout << "We reached the end." << std::endl;
    last_tried = actions.size();
    return {};
}

void fix_program()
{
    size_t attempted_position{std::numeric_limits<size_t>::max()};
    if (!exec_actions(actions))
    {
        while (!exec_actions(get_next_try(attempted_position)));
    }
}

int main()
{
    read_actions();
    fix_program();
    return 0;
}