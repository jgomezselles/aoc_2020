#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <functional>

using rule = std::pair<std::string, std::map<std::string, size_t>>;
using rules = std::map<std::string, std::map<std::string, size_t>>;

rules processed_rules;
const std::string shiny = "shinygold";

std::map<std::string, size_t>
process_values(const std::string &value)
{
    std::map<std::string, size_t> processed;
    std::stringstream ss(value);
    std::string tmp;
    while (std::getline(ss, tmp, ','))
    {
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
        tmp = tmp.substr(0, tmp.find("bag"));
        if (tmp == "noother")
        {
            break;
        }
        auto pos = std::find_if(tmp.rbegin(), tmp.rend(), ::isdigit).base();
        processed.emplace(std::string(pos, tmp.end()), size_t(atoi(std::string(tmp.begin(), pos).c_str())));
    }
    return processed;
}

rule process_rule(const std::string &str_rule)
{
    std::string key = str_rule.substr(0, str_rule.find("bag"));
    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
    std::string value = str_rule.substr(str_rule.find("contain") + 7);
    auto values = process_values(value);
    return {key, values};
}

size_t count_bags(const std::string &bag)
{
    size_t n_bags{1};
    for (const auto &r : processed_rules.at(bag))
    {
        n_bags += (r.second * count_bags(r.first));
    }

    return n_bags;
}

size_t process_rules()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(input, line))
    {
        processed_rules.insert(process_rule(line));
    }

    input.close();
    return count_bags(shiny) - 1;
}

int main()
{
    auto result = process_rules();
    std::cout << "Sum is " << result << "." << std::endl;
    return 0;
}