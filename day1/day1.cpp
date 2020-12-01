#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv)
{
    std::unordered_set<int> previous;
    std::fstream file("input.txt");
    std::string s;
    std::vector<int> numbers;

    // part one
    while(std::getline(file, s))
    {
        int i = std::stoi(s);
        numbers.push_back(i);
        if(previous.find(2020-i) != previous.end())
        {
            std::cout << i * (2020-i) << std::endl;
        }
        else
        {
            previous.insert(i);
        }
        
    }
    // part 2
    for(const auto& a : numbers)
    {
        for(const auto& b : numbers)
        {
            for(const auto& c : numbers)
            {
                if(a+b+c == 2020)
                {
                    std::cout << a*b*c << std::endl;
                }
            }
        }
    }
    return 0;
}