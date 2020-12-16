#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <regex>

using Rule = std::pair<int, int>;
using Rules = std::pair<Rule, Rule>;
/*
    places tokens into a vector, tokens are split on delim
*/
std::vector<int> parseTicket(const std::string& str, const char& delim=',')
{
    std::vector<int> tokens;
    std::stringstream ss;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(std::stoi(ss.str()));
            ss.str(""); // clears stringstream
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(std::stoi(ss.str()));

    return tokens;
}

Rules parseRules(std::string str)
{
    std::regex regexp("[0-9]+"); 
    std::smatch m;
    std::vector<int> numbers;
    while(std::regex_search(str, m, regexp))
    {
        numbers.push_back(std::stoi(m.str()));
        str = m.suffix().str();
    }

    Rule first_rule(numbers[0], numbers[1]);
    Rule second_rule(numbers[2], numbers[3]);

    return Rules(first_rule, second_rule);
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    std::vector<int> my_ticket;
    std::vector<std::vector<int>> neighbor_tickets;
    std::map<std::string, Rules> all_rules;

    // read rules
    while(std::getline(file, s))
    {
        if(s == "")
        {
            break;
        }
        else
        {
            std::string name = s.substr(0, s.find(":"));
            Rules new_rules = parseRules(s);
            all_rules.emplace(name, new_rules);
        }
    }
    // skip newline
    std::getline(file, s);
    // skip name
    std::getline(file, s);
    my_ticket = parseTicket(s);
    // skip newline
    std::getline(file, s);
    // skip name
    std::getline(file, s);
    while(std::getline(file, s))
    {
        neighbor_tickets.push_back(parseTicket(s));
    }
    // part 1
    int error_size = 0;
    for(int i=0; i < neighbor_tickets.size(); ++i)
    {
        for(auto& value : neighbor_tickets[i])
        {
            bool found_good_entry = false;
            for(const auto& ar: all_rules)
            {
                Rule first_rule = ar.second.first;
                Rule second_rule = ar.second.second;
                if((value >= first_rule.first && value <= first_rule.second) ||
                   (value >= second_rule.first && value <= second_rule.second))
                {
                    found_good_entry = true;
                }
            }
            if(!found_good_entry)
            {
                error_size += value;
                neighbor_tickets.erase(neighbor_tickets.begin() + i);
                --i;
                break;
            }
        }
    }
    std::cout << error_size << std::endl;
    // part 2
    std::map<std::string, std::vector<int>> field_to_index;
    neighbor_tickets.push_back(my_ticket);

    for(const auto& ar: all_rules)
    {
        Rule first_rule = ar.second.first;
        Rule second_rule = ar.second.second;
        for(int row=0; row < neighbor_tickets[0].size(); ++row)
        {
            bool found = true;
            for(const auto& nt : neighbor_tickets)
            {
                int value = nt[row];
                if(((value >= first_rule.first && value <= first_rule.second) ||
                   (value >= second_rule.first && value <= second_rule.second)))
                {
                    continue;
                }
                else
                {
                    found = false;
                    break;
                }
                
            }
            if(found)
            {
                field_to_index[ar.first].push_back(row);
            }
        }
    }
    // find which belongs to which, reduce each field by the
    // index that correspond to a field name. Remove that from
    // the vector
    std::map<std::string, int> proposed_field_to_index;
    int row_to_clear;
    while (field_to_index.size() > 0)
    {
        for(auto& fti : field_to_index)
        {
            if(fti.second.size() == 1)
            {
                row_to_clear = fti.second[0];
                proposed_field_to_index.emplace(fti.first, row_to_clear);
                field_to_index.erase(fti.first);
                break;
            }
        }
        // clear row from other fields
        for(auto& fti : field_to_index)
        {
            fti.second.erase(std::find(fti.second.begin(), fti.second.end(), row_to_clear));
        }
    }
    // print ans
    long long sum = 1;
    for(const auto& fti : proposed_field_to_index)
    {
        if(fti.first.find("departure") != std::string::npos)
        {
            sum *= my_ticket[fti.second];
        }
    }
    std::cout << sum << std::endl;
    return 0;
}