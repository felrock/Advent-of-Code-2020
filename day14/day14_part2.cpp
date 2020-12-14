#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

const int MEMORY_SIZE = 36;

long long binStringToLong(const std::string& bin)
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

std::vector<std::string> applyMask(const std::string& mask, const std::string& value)
{
    long t = 0;
    std::vector<std::string> ret{""};

    for(int i=0; i < mask.size(); ++i)
    {
        int size = ret.size();
        for(int j=0; j < size; ++j)
        {
            if(mask[i] == 'X')
            {
                // add both
                ret.push_back(ret[j] + '0');
                ret[j] += '1';
            }
            else if(value[i] == '1' || mask[i] == '1')
            {
                ret[j] += '1';
            }
            else
            {
                ret[j] += '0';
            }
        }
    }
    return ret;
}

std::string getParameter(const std::string& str)
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
            std::string index_as_string = s.substr(s.find('[')+1, s.find(']')-4);
            long long index_as_long = std::stol(index_as_string);
            const std::vector<std::string>& newValues = applyMask(mask, decimalLongToBinString(index_as_long));
            for(const auto& str : newValues)
            {
                long long index = binStringToLong(str);
                memory[index] = std::stol(getParameter(s));
            }
        }
    }
    long long sum = 0;
    for(const auto& mem : memory)
    {
        sum += mem.second;
    }
    std::cout << "part 2: " << sum << std::endl;
    return 0;
}