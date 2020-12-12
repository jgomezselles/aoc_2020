#include <iostream>
#include <fstream>

bool validate(const std::string &pass)
{
    auto hyphen = pass.find("-");
    int min = std::atoi(pass.substr(0, hyphen).c_str());
    auto first_space = pass.find(" ");
    int max = std::atoi(pass.substr(hyphen + 1, first_space - (hyphen + 1)).c_str());
    auto colon = pass.find(":");
    char letter = pass.substr(first_space + 1).front();
    std::string actual_pass = pass.substr(colon + 2);

    bool first_found = actual_pass.at(min - 1) == letter;
    bool second_found = actual_pass.at(max - 1) == letter;

    return first_found ^ second_found;
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