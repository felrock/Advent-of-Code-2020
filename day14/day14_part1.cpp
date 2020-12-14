#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

const int MEMORY_SIZE = 36;

long long binStringToLong(std::string bin)
{
    long long ret = 0;
    for(int i=0; i < bin.size(); ++i)
    {
        if(bin[i] == '1')
        {
            ret += 1;
        }
        ret <<= 1;
    }
    ret >>= 1;
    return ret;
}

std::string decimalLongToBinString(long long dec)
{
    std::string ret = "";
    int i=0;
    while(i < MEMORY_SIZE)
    {
        if(dec & 1)
        {
            ret = "1" + ret;
        }
        else
        {
            ret = "0" + ret;
        }
        dec >>= 1;
        i++;
    }
    return ret;
}

std::string applyMask(std::string mask, std::string value)
{
    long t = 0;
    std::string ret = "";
    for(int i=0; i < MEMORY_SIZE; ++i)
    {
        if(mask[i] == '0')
        {
            ret += '0';
        }
        else if(mask[i] == '1')
        {
            ret += '1';
        }
        else
        {
            ret += value[i];
        }
    }
    return ret;
}

std::string getParameter(std::string str)
{
    return str.substr(str.find('=')+2, std::string::npos);
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s, mask;

    std::map<long long, long long> memory;
    while(std::getline(file, s))
    {
        std::string first_word = s.substr(0, s.find(' '));
        if(first_word == "mask")
        {
            // set new mask
            mask = getParameter(s);
        }
        else
        {
            // apply mask to values
            long long para_as_long = std::stol(getParameter(s));
            std::string long_as_string = decimalLongToBinString(para_as_long);
            std::string newValue = applyMask(mask, long_as_string);
            std::string index_as_string = s.substr(s.find('[')+1, s.find(']')-4);
            long index = std::stol(index_as_string);
            long final = binStringToLong(newValue);

            memory[index] = binStringToLong(newValue);
        }
    }
    long long sum = 0;
    for(const auto& mem : memory)
    {
        sum += mem.second;
    }
    std::cout << "part 1: " << sum << std::endl;
    return 0;
}