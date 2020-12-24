#include <iostream>
#include <deque>
#include <fstream>

int mod(int a, int b)
{
  return a > 0 ? a % b : (a+b) % b;
}

void remove(std::deque<int>& vec, int val)
{
  for(int i=0; i < vec.size(); ++i)
  {
    if(val == vec[i])
    {
      vec.erase(vec.begin() +i);
      break;
    }
  }
}

int find(const std::deque<int>& vec, const int& val)
{
  for(int i=0; i < vec.size(); ++i)
  {
    if(vec[i] == val)
    {
      return i;
    }
  }
  return -1;
}

int main(int argc, char** argv)
{
  std::fstream file(argv[1]);
  std::string s;

  std::deque<int> cups;

  // read single line input
  std::getline(file, s);
  int max = -1;
  for(const auto& chr : s)
  {
    int num = chr - '0';
    cups.push_back(num);
    if(num > max)
    {
      max = num;
    }
  }
  int width = cups.size();

  // iterate game
  for(int i=0; i < 100; ++i)
  {
    int current_cup = cups[i % width];

    // remove three cups clockwise of current cup
    int first_cup   = cups[(i+1) % width];
    int second_cup  = cups[(i+2) % width];
    int third_cup   = cups[(i+3) % width];

    // find the destination cup
    int dest   = current_cup - 1;
    int start  = i % width;
    int index  = (i+1) % width;
    bool found = false;
    while(true)
    {
      if(dest == cups[index] && cups[index] != first_cup &&
         cups[index] != second_cup && cups[index] != third_cup)
      {
        break;
      }
      else if(index == start)
      {
        index = start;
        dest = mod(dest-1, max+1);
      }
      index = (index+1) % width;
    }

    // re-arrange the list first
    for(int j=0; j < (i % width); ++j)
    {
      int t_val = cups[0];
      cups.pop_front();
      cups.push_back(t_val);
    }

    // make the switch
    remove(cups, first_cup);
    remove(cups, second_cup);
    remove(cups, third_cup);

    index = (find(cups, dest) + 1) % width;
    cups.insert(cups.begin()+index, first_cup);
    index = (find(cups, dest) + 2) % width;
    cups.insert(cups.begin()+index, second_cup);
    index = (find(cups, dest) + 3) % width;
    cups.insert(cups.begin()+index, third_cup);

    // re-arrange the list first
    for(int j=0; j < (i % width); ++j)
    {
      int t_val = cups[width-1];
      cups.pop_back();
      cups.push_front(t_val);
    }
  }

  // move after 1
  for(int i=0; i < cups.size(); ++i)
  {
    if(cups[0] == 1)
    {
      break;
    }
    else
    {
      int t_val = cups[0];
      cups.pop_front();
      cups.push_back(t_val);
    }
  }

  for(const auto& k : cups)
  {
    std::cout << k;
  }
  std::cout << std::endl;
  return 0;
}
