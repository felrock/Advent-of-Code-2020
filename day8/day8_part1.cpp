#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;
    std::vector<std::pair<std::string, int>> program;

    while(std::getline(file, s))
    {
        std::string instuction = s.substr(0, s.find(" "));
        int number             = std::stoi(s.substr(s.find(" ")+1, s.size()));

        program.push_back(std::pair<std::string, int >(instuction, number));
    }

    int acc = 0;
    std::set<int> visited;

    for(int pc=0; pc < program.size(); ++pc)
    {
        if(visited.find(pc) != visited.end())
        {
            // infinite loop found
            break;
        }
        visited.insert(pc);
        if(program[pc].first == "jmp")
        {
            // substract one beacause the loop will increment
            pc += program[pc].second - 1;
        }
        else if(program[pc].first == "acc")
        {
            acc += program[pc].second;
        }
    }
    std::cout << acc << std::endl;

    return 0;
}