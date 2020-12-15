#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

/*
    places tokens into a vector, tokens are split on delim
*/
std::vector<int> getTokens(const std::string& str, const char& delim)
{
    std::vector<int> tokens;
    std::stringstream ss;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(std::stoi(ss.str()));
            ss.str(""); // clears stringstream
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(std::stoi(ss.str()));

    return tokens;
}

int findLatestOf(std::vector<int> vec, int num)
{
    for(int i=vec.size()-2; i >= 0; --i)
    {
        if(vec[i] == num)
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

    std::getline(file, s);
    std::vector<int> memory = getTokens(s, ',');
    int i = memory.size();
    while(i < 2020)
    {
        int latest_occurence = findLatestOf(memory, memory[i-1]);
        if(latest_occurence < 0)
        {
            memory.push_back(0);
        }
        else
        {
            int age = i - (latest_occurence+1);

            memory.push_back(age);
        }
        i++;
    }
    std::cout << memory[i-1] << std::endl;
    return 0;
}