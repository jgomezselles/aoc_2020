#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <optional>
#include <exception>

bool validate(const std::string &password)
{
    std::string tmp = password;
    auto hyphen = tmp.find("-");
    if (hyphen == std::string::npos)
    {
        throw std::logic_error("- not found");
    }

    int min = std::atoi(tmp.substr(0, hyphen).c_str());

    auto first_space = tmp.find(" ");
    if (first_space == std::string::npos)
    {
        throw std::logic_error("first space not found");
    }
    int max = std::atoi(tmp.substr(hyphen + 1, first_space - (hyphen + 1)).c_str());

    auto colon = tmp.find(":");
    if (colon == std::string::npos)
    {
        throw std::logic_error(": not found");
    }

    std::string letter = tmp.substr(first_space + 1, colon - (first_space + 1)).c_str();
    if (letter.size() != 1)
    {
        throw std::logic_error("Found size of letter: " + letter.size());
    }

    std::string actual_pass = tmp.substr(colon + 1); //including space. If problem, remove it with a "colon+2"

    auto n_letters = std::count(actual_pass.begin(), actual_pass.end(), letter.front());
    return n_letters >= min && n_letters <= max;
}

int get_valid_passwords()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return 0;
    }

    int valid_passwords{0};
    std::string line;
    while (std::getline(input, line))
    {
        if (!line.size())
        {
            continue;
        }

        if (validate(line))
        {
            ++valid_passwords;
        }
    }

    input.close();

    return valid_passwords;
}

int main()
{
    auto numbers = get_valid_passwords();

    std::cout << "Number of valid passwords is " << numbers << "." << std::endl;
    return 0;
}