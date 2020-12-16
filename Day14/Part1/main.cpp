#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

std::string get_mask(const std::string &mask_line)
{
    return mask_line.substr(7);
}

void apply_mask(std::bitset<36> &bits, const std::string &mask)
{
    size_t bit_pos{0};
    for (auto it = mask.rbegin(); it != mask.rend(); ++it)
    {
        switch (*it)
        {
        case 'X':
            break;
        case '1':
            bits.set(bit_pos);
            break;
        case '0':
            bits.reset(bit_pos);
            break;
        default:
            break;
        }
        ++bit_pos;
    }
}

void add_to_mem(std::map<size_t, size_t> &mem, const std::string &line, const std::string &mask)
{
    size_t mempos = atoi(line.substr(line.find('[') + 1, line.find(']')).c_str());
    std::bitset<36> b(atoi(line.substr(line.find("= ") + 2).c_str()));
    apply_mask(b, mask);
    mem.insert_or_assign(mempos, b.to_ullong());
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