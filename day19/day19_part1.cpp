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
    const std::string& rule_start, const std::string& rule_current)
{
  if(rule_map.find(rule_current) == rule_map.end())
  {
    return std::vector<std::string>{rule_current};
  }

  const std::string delim   = "|";
  std::vector<std::string> expanded_rule;
  std::vector<Rules> rules  = rule_map.at(rule_current);
  for(int i=0; i < rules.size(); ++i)
  {
    std::string concat_str = "";
    std::vector<std::string> new_expanded_rule = {""};
    for(const auto& rule : rules[i])
    {
      std::vector<std::string> result = expandRule(rule_map, rule_start, rule);
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
  std::vector<std::string> expanded_rule = expandRule(rule_map, "0", "0");
  int count = 0;
  while(std::getline(file, s))
  {
    for(const auto& er : expanded_rule)
    {
      if(er == s)
      {
        count++;
        break;
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}
