#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

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

static const std::map<action, std::string> action_to_str{
    {action::NOP, "nop"},
    {action::JUMP, "jmp"},
    {action::ACC, "acc"}};

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

struct state
{
    size_t pos{0};
    int accum{0};
    std::set<size_t> actions_executed{};
};

void exec_action(state &st)
{
    const auto &[a, n] = actions.at(st.pos);

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

void exec_actions()
{
    state st;
    while (st.pos < actions.size())
    {
        if (const auto [_, is_new] = st.actions_executed.insert(st.pos); !is_new)
        {
            std::cout << "We were already here! Preventing execution." << std::endl;
            std::cout << "Pos " << st.pos << std::endl;
            std::cout << "Accum " << st.accum << std::endl;
            return;
        }
        exec_action(st);
    }

    std::cout << "We reached the end." << std::endl;
    std::cout << "Pos " << st.pos << std::endl;
    std::cout << "Accum " << st.accum << std::endl;
}

int main()
{
    read_actions();
    exec_actions();

    return 0;
}