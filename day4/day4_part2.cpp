#include "Field.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

/*
    places tokens into a vector, tokens are split on delim
*/
std::vector<std::string> getTokens(const std::string& str, const char& delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(ss.str());
            ss.str(""); // clears stringstream
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(ss.str()); 
    return tokens;
}
/*
    checks if all mandatory fields are found
*/
bool checkIfMandatoryFound(const std::unordered_set<std::string>& found, const std::vector<std::string>& mandatory)
{
    for(const auto& str : mandatory)
    {
        if(found.find(str) == found.end())
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

    const std::string new_passport = "";
    const std::vector<std::string> mandatory_vec = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    std::unordered_map<std::string, std::unique_ptr<Field>> mandatory_map;
    mandatory_map["byr"] = std::make_unique<byr>();
    mandatory_map["iyr"] = std::make_unique<iyr>();
    mandatory_map["eyr"] = std::make_unique<eyr>();
    mandatory_map["hgt"] = std::make_unique<hgt>();
    mandatory_map["hcl"] = std::make_unique<hcl>();
    mandatory_map["ecl"] = std::make_unique<ecl>();
    mandatory_map["pid"] = std::make_unique<pid>();

    std::unordered_set<std::string> found;
    int password_count = 0;

    while(std::getline(file, s))
    {
        if(s == new_passport)
        {
            if(checkIfMandatoryFound(found, mandatory_vec))
            {
                ++password_count;
            }
            found.clear();
        }
        else
        {
            const std::vector<std::string>& tokens = getTokens(s, ' ');

            for(const auto& token : tokens)
            {
                std::string key = token.substr(0, 3);
                std::string value = token.substr(token.find(":")+1, token.size());
                if(mandatory_map.find(key) != mandatory_map.end())
                {
                     if(mandatory_map[key]->checkIfValid(value))
                    {
                        found.insert(key);
                    }
                }
            }
        }
    }
    // check the last passport fields
    if(checkIfMandatoryFound(found, mandatory_vec))
    {
        ++password_count;
    }
    std::cout << "Part 2: " << password_count << std::endl;
}