#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

/*
    Check if the program given terminates or runs in an endless loop
*/
std::pair<bool, int> terminates(const std::vector<std::pair<std::string, int>>& program)
{
    int accumulator = 0;
    std::set<int> visited;

    for(int pc=0; pc < program.size(); ++pc)
    {
        if(visited.find(pc) != visited.end())
        {
            // infinite loop found
            return std::pair<bool, int>(false, accumulator);
        }
        visited.insert(pc);
        if(program[pc].first == "jmp")
        {
            // substract one beacause the loop will increment
            pc += program[pc].second - 1;
        }
        else if(program[pc].first == "acc")
        {
            accumulator += program[pc].second;
        }
    }
    return std::pair<bool, int>(true, accumulator);
}

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
    int change_at = 0;

    while(true)
    {
        std::vector<std::pair<std::string, int>> new_program = program;

        // swap instuction
        while(change_at < new_program.size())
        {
            if(new_program[change_at].first == "jmp")
            {
                new_program[change_at++] = std::pair<std::string, int>("nop", new_program[change_at].second);
                break;
            }
            else if(new_program[change_at].first == "nop")
            {
                new_program[change_at++] = std::pair<std::string, int>("jmp", new_program[change_at].second);
                break;
            }
            change_at++;
        }
        // run program with swapped instruction
        std::pair<bool, int> runs = terminates(new_program);
        if(runs.first)
        {
            std::cout << runs.second << std::endl;
            return 0;
        }
    }
    return 0;
}