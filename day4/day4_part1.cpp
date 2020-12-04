#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

bool isValidPassport(const std::unordered_set<std::string>& found, const std::vector<std::string>& mandatory)
{
    for(const auto& man : mandatory)
    {
        if(found.find(man) == found.end())
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "pass input file" << std::endl;
        return 0;
    }
    std::fstream file(argv[1]);
    std::string s;

    const std::vector<std::string> mandatory = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    const std::string new_passport = "";

    std::unordered_set<std::string> found;
    int password_count = 0;

    while(std::getline(file, s))
    {
        if(s == new_passport)
        {
            if(isValidPassport(found, mandatory))
            {
                ++password_count;
            }
            // reset map for next section
            found.clear();
        }
        // add found strings
        for(const auto& man : mandatory)
        {
            if(s.find(man) != std::string::npos)
            {
                found.insert(man);
            }
        }
    }
    // the latest section might be valid so check again
    if(s == new_passport)
    {
        if(isValidPassport(found, mandatory))
        {
            ++password_count;
        }
    }
    std::cout << password_count << std::endl;
}