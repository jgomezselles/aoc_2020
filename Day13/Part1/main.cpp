#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

std::pair<size_t, std::vector<size_t>> read_notes()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        return {};
    }

    std::string tmp;
    std::getline(input, tmp);
    size_t min_time = atoi(tmp.c_str());
    std::getline(input, tmp);
    input.close();

    std::stringstream ss(tmp);
    std::vector<size_t> v_ids;
    while (std::getline(ss, tmp, ','))
    {
        if (tmp != "x")
        {
            v_ids.push_back(atoi(tmp.c_str()));
        }
    }
    return {min_time, v_ids};
}

size_t result(const size_t min_time,const std::vector<std::size_t>& ids)
{
    std::map<size_t, size_t> closests;
    for(const auto& id : ids)
    {
        auto closest = id;
        while(closest <= min_time)
        {
            closest += id;
        }
        closests.insert_or_assign(closest,id);
    }
    
    const auto& [timestamp, id] = *closests.begin();
    return id * (timestamp - min_time);
}

int main()
{
    const auto [min_time, ids] = read_notes();
    std::cout << "Result is: " << result(min_time, ids) << std::endl;

    return 0;
}