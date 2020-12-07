#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <unordered_map>

using Bag  = std::pair<std::string, int>;
using Bags = std::vector<Bag>;

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
    parse string to retrieve the bags that are contained in the parent bag
*/
Bags getContainingBags(const std::string& str)
{
    const std::string bag_split1 = "bag";
    const std::string bag_split2 = "bags";

    Bags contains;
    int num = -1;
    std::string name = "";
    bool num_found = false;

    std::vector<std::string> tokens = getTokens(str, ' ');

    for(const auto& token : tokens)
    {
        if((token.find(bag_split1) != std::string::npos || token.find(bag_split2) != std::string::npos) && num != -1)
        {
            num_found = false;
            contains.emplace_back(name, num);
            name = "";
        }
        else if(token.size() == 1 && std::isdigit(token[0]))
        {
            num = std::stoi(token);
            num_found = true;
        }
        else if(num_found)
        {
            // avoid space at start of name
            name = name == "" ? token : name + " " + token;
        }
    }

    return contains;
}

/*
    walk from a given bag location towards goal bag, if not found return false, if found return true
*/
bool walkToBag(const std::unordered_map<std::string, Bags>& bags, const std::string& start, const std::string& goal)
{
    if(bags.find(start) == bags.end())
    {
        return false;
    }
    for(const auto& bag : bags.at(start))
    {
        if(bag.first == goal || walkToBag(bags, bag.first, goal))
        {
            return true;
        }
    }
    return false;
}

/*
    count amount of bags that fit in the start bag, descend into each child bag and multiply by
    each bag amount location in parent bag.
*/
int countBagSizes(const std::unordered_map<std::string, Bags>& bags, const std::string& start)
{
    if(bags.find(start) == bags.end())
    {
        return 0;
    }
    int found = 0;
    for(const auto& bag : bags.at(start))
    {
        found += bag.second + (bag.second * countBagSizes(bags, bag.first));
    }
    return found;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    const std::string parent_bag_split = "bags";
    const std::string goal_bag         = "shiny gold";

    std::unordered_map<std::string, Bags> bag_map;
    
    while(std::getline(file, s))
    {
        std::string current_bag = s.substr(0, s.find(parent_bag_split)-1);
        const Bags& contains = getContainingBags(s);

        for(const auto& bag : contains)
        {
            bag_map[current_bag].push_back(bag);
        }
    }
    int contains_goal = 0;
    for(const auto& bag : bag_map)
    {
        if(walkToBag(bag_map, bag.first, goal_bag))
        {
            ++contains_goal;
        }
    }
    std::cout << "Part 1: " << contains_goal << std::endl;
    std::cout << "Part 2: " << countBagSizes(bag_map, goal_bag) << std::endl;

    return 0;
}