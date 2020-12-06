#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv)
{
  std::fstream file(argv[1]);
  std::string s;

  const std::string new_group = "";
  std::unordered_set<char> group_answers;
  int question_answered = 0;

  while(std::getline(file, s))
  {
    if(s == new_group)
    {
      question_answered += group_answers.size();
      group_answers.clear();
    }
    else
    {
      for(const auto& chr : s)
      {
        group_answers.insert(chr);
      }
    }
  }
  // add last groups answers to total
  std::cout << question_answered + group_answers.size() << std::endl;

  return 0;
}
