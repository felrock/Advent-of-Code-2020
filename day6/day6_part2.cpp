#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <vector>

int main(int argc, char** argv)
{
  std::fstream file(argv[1]);
  std::string s;

  const std::string new_group = "";
  std::unordered_map<char, int> group_answers;
  int group_size = 0;
  int question_answered = 0;

  std::function<bool(const std::pair<char, int>& p)> cmp;
  cmp = [&group_size](const std::pair<char, int>& pair)
  {
    return group_size == pair.second;
  };

  while(std::getline(file, s))
  {
    if(s == new_group)
    {
      question_answered +=std::count_if(group_answers.begin(),
        group_answers.end(),
        cmp
      );
      group_answers.clear();
      group_size = 0;
    }
    else
    {
      for(const auto& chr : s)
      {
        ++group_answers[chr];
      }
      ++group_size;
    }
  }
  // check last group
  question_answered +=std::count_if(group_answers.begin(),
    group_answers.end(),
    cmp
  );
  std::cout << question_answered << std::endl;

  return 0;
}
