#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>

using Rules = std::vector<std::string>;

std::vector<Rules> parseRule(std::string str)
{
  std::vector<Rules> all_rules;
  Rules rules;
  std::string num = "";
  bool skip = true;
  for(const auto& chr : str)
  {
    if(chr == ' ' && num != "")
    {
      rules.push_back(num);
      num = "";
    }
    else if(chr == '|')
    {
      all_rules.push_back(rules);
      rules = {};
    }
    else if(chr != ' ')
    {
      num += chr;
    }
  }
  rules.push_back(num);
  all_rules.push_back(rules);
  return all_rules;
}


std::vector<std::string> expandRule(const std::unordered_map<std::string, std::vector<Rules>>& rule_map,
    const std::string& current,
    std::unordered_map<std::string, int>& visits,
    const int depth)
{
  if(rule_map.find(current) == rule_map.end())
  {
    return std::vector<std::string>{current};
  }

  std::vector<std::string> expanded_rule;
  std::vector<Rules> rules  = rule_map.at(current);
  for(int i=0; i < rules.size(); ++i)
  {
    std::vector<std::string> new_expanded_rule = {""};
    for(const auto& rule : rules[i])
    {
      if(visits[rule] >= depth)
      {
        continue;
      }
      visits[rule] += 1;
      std::vector<std::string> result = expandRule(rule_map, rule, visits, depth);
      std::vector<std::string> temp;
      for(const auto& res : result)
      {
        for(const auto& ner : new_expanded_rule)
        {
          temp.push_back(ner + res);
        }
      }
      new_expanded_rule = temp;
    }
    expanded_rule.insert(expanded_rule.end(), new_expanded_rule.begin(), new_expanded_rule.end());
  }
  return expanded_rule;
}

int main(int argc, char** argv)
{
  std::string s;
  std::fstream file(argv[1]);

  std::unordered_map<std::string, std::vector<Rules>> rule_map;

  while(std::getline(file, s))
  {
    if(s == "")
    {
      // finished reading rules
      break;
    }
    std::string rule_name = s.substr(0, s.find(":"));
    std::string rule_str = s.substr(s.find(":")+2, s.size()-1);
    if(s.find("\"") != std::string::npos)
    {
      Rules rule = {rule_str.substr(rule_str.find_first_of("\"")+1,
                    rule_str.find_last_of("\"")-1)};
      rule_map[rule_name] = {rule};
    }
    else
    {
      rule_map[rule_name] = parseRule(rule_str);
    }
  }
  std::vector<std::string> strings;
  int max_size = 0;
  {
    if(s.size() > max_size)
    {
      max_size = s.size();
    }
    strings.push_back(s);
  }
  std::unordered_map<std::string, int> visits;
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 1);
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 2);
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 3);
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 4);
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 5);
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", visits, 6);
  int count = 0;
  while(std::getline(file, s))
  {
    for(const auto& r : expanded_rule)
    {
      if(s == r)
      {
        count++;
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}
