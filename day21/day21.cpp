#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> getTokens(const std::string& str, const char& delim)
{
    std::stringstream ss;
    std::vector<std::string> tokens;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(ss.str());
            ss.str("");
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(ss.str());

    return tokens;
}

int main(int argc, char** argv)
{
    std::string s;
    std::fstream file(argv[1]);

    std::unordered_set<std::string> allergens_set;
    std::unordered_map<std::string, int> ingredients_map;

    std::vector<std::vector<std::string>> ingredients_vec;
    std::vector<std::vector<std::string>> allergens_vec;

    while(std::getline(file, s))
    {
        if(s.find("(") != std::string::npos)
        {
            s.erase(std::remove(s.begin(), s.end(), '('), s.end());
        }
        if(s.find(")") != std::string::npos)
        {
            s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
        }
        if(s.find(",") != std::string::npos)
        {
            s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        }
        int div = s.find("contains ");

        // parse line
        std::vector<std::string> ingredients_line = getTokens(s.substr(0, div-1), ' ');
        std::vector<std::string> allergens_line = getTokens(s.substr(div+9, s.size()-div-9), ' ');

        // add all allergens
        for(const auto& allergen : allergens_line)
        {
            allergens_set.insert(allergen);
        }
        // make the count here for part 1, used later
        for(const auto& ingredient : ingredients_line)
        {
            ingredients_map[ingredient] += 1;
        }

        ingredients_vec.push_back(ingredients_line);
        allergens_vec.push_back(allergens_line);
    }
    // all allergens must have a ingredient, but not the other way around
    // reduce allergens_set until all allergens have been found
    std::unordered_map<std::string, std::string> taken;
    while(allergens_set.size() > 0)
    {
        for(const auto& allergen : allergens_set)
        {
            // iterate all input lines, count ingredients in the lines with corresponding
            // allergen
            std::unordered_map<std::string, int> ingredient_per_allergen;
            for(int i=0; i < ingredients_vec.size(); ++i)
            {
                if(std::count(allergens_vec[i].begin(), allergens_vec[i].end(), allergen) == 1)
                {
                    for(const auto& ingredient : ingredients_vec[i])
                    {
                        // check that the ingredient isn't already taken by another allergen
                        if(taken.find(ingredient) == taken.end())
                        {
                            ingredient_per_allergen[ingredient] += 1;
                        }
                    }
                }
            }
            // check which ingredient is the most mentioned
            std::string most_seen;
            int max_count = 0;
            for(const auto& ipg : ingredient_per_allergen)
            {
                if(ipg.second > max_count)
                {
                    most_seen = ipg.first;
                    max_count = ipg.second;
                }
            }
            // make sure the ingredient have a unique max_count
            int count_of_max = std::count_if(ingredient_per_allergen.begin(),
                                          ingredient_per_allergen.end(),
                                          [max_count](const std::pair<std::string, int>& t){ return t.second == max_count;});
            if(count_of_max == 1)
            {
                taken[most_seen] = allergen;
                allergens_set.erase(allergen);
                break;
            }
        }
    }
    // part 1
    int sum = 0;
    for(const auto& ingredient : ingredients_map)
    {
        if(taken.find(ingredient.first) == taken.end())
        {
            sum += ingredient.second;
        }
    }
    std::cout << "part 1: " << sum << std::endl;
    std::vector<std::pair<std::string, std::string>> list;
    for(const auto& taken_pair : taken)
    {
        list.push_back({taken_pair.first, taken_pair.second});
    }
    // part 2
    std::sort(list.begin(), list.end(), [](auto a, auto b){ return a.second < b.second;});
    std::string str;
    for(const auto& itm : list)
    {
        str += itm.first + ",";
    }
    std::cout << "part 2: " << str.substr(0, str.size()-2) << std::endl;

    return 0;
}