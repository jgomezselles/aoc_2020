#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <bitset>

std::string get_mask(const std::string &mask_line)
{
    return mask_line.substr(7);
}

void add_permutations(std::set<size_t> &memory_positions, const size_t floating_position)
{
    const auto base = memory_positions;
    for(const auto& mem : base)
    {
        auto new_position = std::bitset<36>(mem);
        new_position.flip(floating_position);
        memory_positions.insert(new_position.to_ullong());
    }
}

std::set<size_t> get_memory_positions(const size_t &mempos_base, const std::string &mask)
{
    size_t bit_pos{0};
    std::bitset<36> bits_base(mempos_base);
    std::vector<size_t> floating_pos;

    for (auto it = mask.rbegin(); it != mask.rend(); ++it)
    {
        switch (*it)
        {
        case 'X':
            floating_pos.push_back(bit_pos);
            break;
        case '1':
            bits_base.set(bit_pos);
            break;
        case '0':
            break;
        default:
            break;
        }
        ++bit_pos;
    }

    std::set<size_t> memory_positions {bits_base.to_ullong()};
    for(const auto& pos : floating_pos)
    {
        add_permutations(memory_positions, pos);
    }

    return memory_positions;
}

void add_to_mem(std::map<size_t, size_t> &mem, const std::string &line, const std::string &mask)
{
    size_t mempos_base = atoi(line.substr(line.find('[') + 1, line.find(']')).c_str());
    size_t value = atoi(line.substr(line.find("= ") + 2).c_str());
    for (const auto &mem_pos : get_memory_positions(mempos_base, mask))
    {
        mem.insert_or_assign(mem_pos, value);
    }
}

size_t run_program()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string tmp;
    std::getline(input, tmp);
    std::string mask = get_mask(tmp);

    std::map<size_t, size_t> mem;

    while (std::getline(input, tmp))
    {
        if (tmp.at(3) != '[')
        {
            mask = get_mask(tmp);
        }
        else
        {
            add_to_mem(mem, tmp, mask);
        }
    }

    size_t sum{0};
    for (const auto &[_, v] : mem)
    {
        sum += v;
    }

    return sum;
}

int main()
{
    std::cout << "Result is: " << run_program() << std::endl;

    return 0;
}