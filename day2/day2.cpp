#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    std::fstream file("input.txt");
    std::string s;
    int passwords_p1 = 0;
    int passwords_p2 = 0;
    std::vector<std::string> input;

    while(std::getline(file, s))
    {
        // parsing the input value
        int minVal     = std::stoi(s.substr(0, s.find("-")));
        int maxVal     = std::stoi(s.substr(s.find("-")+1,s.find(" ")));
        char letter    = s[s.find(" ")+1];
        std::string pw = s.substr(s.find(":")+2, s.size());
        
        // counting letters for part one
        size_t count = std::count(pw.begin(), pw.end(), letter);
        if( count >= minVal && count <= maxVal)
        {
            ++passwords_p1;
        }
        // exclusive or between selected indexes
        if((pw[minVal-1] == letter) ^ (pw[maxVal-1] == letter))
        {
            ++passwords_p2;
        }
    }
    std::cout << "part one: " << passwords_p1 << std::endl;
    std::cout << "part two: " << passwords_p2 << std::endl;
    
    return 0;
}