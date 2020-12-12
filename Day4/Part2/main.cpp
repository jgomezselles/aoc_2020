#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <map>
#include <regex>

std::map<std::string, std::string> mandatory_fields{
    {"byr", "^19[2-9][0-9]|200[0-2]$"},
    {"iyr", "^20(1[0-9]|20)$"},
    {"eyr", "^20(2[0-9]|30)$"},
    {"hgt", "^(1([5-8][0-9]|[9][0-3])cm)|((59|6[0-9]|7[0-6])in)$"},
    {"hcl", "^#[0-9|a-zA-Z]{6}$"},
    {"ecl", "^(amb|blu|brn|gry|grn|hzl|oth)$"},
    {"pid", "^[0-9]{9}$"}};

bool is_valid(const std::string &passport)
{
    std::stringstream ss(passport);
    std::string tmp;
    std::vector<std::string> kv_pairs;
    while (std::getline(ss, tmp, ' '))
    {
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
        kv_pairs.push_back(tmp);
    }
    std::map<std::string, std::string> tokenized;
    for (const auto &kv : kv_pairs)
    {
        std::stringstream ss2(kv);
        std::string tmp2, key, value;
        size_t count{0};
        while (std::getline(ss2, tmp2, ':'))
        {
            if (count == 0)
            {
                key = tmp2;
            }
            else if (count == 1)
            {
                value = tmp2;
            }
            else
            {
                throw std::logic_error("WTF");
            }
            ++count;
        }
        if (key.size() && value.size())
        {
            tokenized[key] = value;
        }
    }

    for (const auto &[field, regex_str] : mandatory_fields)
    {
        const auto &it = tokenized.find(field);
        if (it == tokenized.end())
        {
            return false;
        }

        const std::regex regex(regex_str);
        if (!std::regex_search(it->second, regex))
        {
            return false;
        }
    }
    return true;
}

size_t count_valid_passports()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string line;
    size_t valid{0};
    std::string buff;
    while (std::getline(input, line))
    {
        buff += " ";
        buff += line;
        if (!line.size())
        {
            valid += is_valid(buff);
            buff.clear();
        }
    }

    buff += " ";
    buff += line;
    valid += is_valid(buff);
    buff.clear();

    input.close();

    return valid;
}

int main()
{
    auto result = count_valid_passports();
    std::cout << "Number of valid passports is " << result << "." << std::endl;
    return 0;
}