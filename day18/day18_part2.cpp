#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>

std::vector<std::string> getTokens(const std::string& str, const char& delim)
{
    std::stringstream ss;
    std::vector<std::string> tokens;
    for(const auto& chr : str)
    {
        if(chr == delim)
        {
            tokens.push_back(ss.str());
            ss.str("");
        }
        else
        {
            ss << chr;
        }
    }
    tokens.push_back(ss.str());

    return tokens;
}

std::pair<int, int> findBrackets(const std::string& str)
{
    int start=0; 
    int end=str.size()-1;
    for(int i=0; i < str.size(); ++i)
    {
        if(str[i] == '(')
        {
            start = i+1;
        }
        if(str[i] == ')')
        {
            end = i-start;
            break;
        }
    }

    return std::make_pair(start, end);
}

std::string reduce(std::string str)
{
    std::vector<std::string> split = getTokens(str, ' ');
    std::deque<std::string> ops;
    std::deque<std::string> nums;
    for(const auto& sp : split)
    {
        if(sp == "+" || sp == "*")
        {
            ops.push_back(sp);
        }
        else
        {
            nums.push_back(sp);
        }
        
    }
    for(int i=0; i < ops.size(); ++i)
    {
        if(ops[i] == "+")
        {
            std::string new_num = std::to_string(std::stoll(nums[i]) + std::stoll(nums[i+1]));
            nums.pop_front();
            nums.pop_front();
            nums.push_front(new_num);
            ops.pop_front();
            i-=1;
        }
    }
    for(int i=0; i < ops.size(); ++i)
    {
        std::string new_num = std::to_string(std::stoll(nums[i]) * std::stoll(nums[i+1]));
        nums.pop_front();
        nums.pop_front();
        nums.push_front(new_num);
        ops.pop_front();
        i-=1;
    }
    return nums[0];
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // read 
    long long sum = 0;
    while(std::getline(file, s))
    {
        std::string str = s;
        while(str.find("(") != std::string::npos)
        {
            std::pair<int, int> indexes = findBrackets(str);
            std::string reduced = reduce(str.substr(indexes.first, indexes.second));
            int last_piece = indexes.first + indexes.second+1;
            str = str.substr(0, indexes.first-1) + reduced + str.substr(last_piece, str.size()-last_piece);
        }
        sum += std::stoll(reduce(str));
    }
    std::cout << sum << std::endl;
    return 0;
}