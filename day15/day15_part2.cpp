#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>

/*
    places tokens into a vector, tokens are split on delim
*/
std::vector<long> getTokens(const std::string& str, const char& delim)
{
    std::vector<long> tokens;
    std::stringstream ss;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(std::stol(ss.str()));
            ss.str(""); // clears stringstream
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(std::stol(ss.str()));

    return tokens;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;
    std::getline(file, s);
    std::vector<long> memory = getTokens(s, ',');

    // key=number, value=index
    std::unordered_map<long, long> latest_seen;
    for(int i=0; i < memory.size()-1; ++i)
    {
        latest_seen.emplace(memory[i], i);
    }
    long i = memory.size();
    int current = memory[i-1];
    int prev = current;

    while(i < 30000000)
    {
        int prev = current;
        if(latest_seen.find(prev) == latest_seen.end())
        {
            current = 0;
        }
        else
        {
            int number_seen_before = latest_seen[prev];
            int age = i - (number_seen_before+1);

            current = age;
        }
        latest_seen[prev] = i-1;
        i++;
    }
    std::cout  << current << std::endl;
    return 0;
}