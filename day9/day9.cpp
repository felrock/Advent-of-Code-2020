#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

/*
    iterate and check if any two numbers sum to given sum
*/
bool checkIfSum(long long sum, std::deque<long long> numbers)
{
    for(int i=0; i < numbers.size(); ++i)
    {
        for(int j=0; j < numbers.size(); ++j)
        {
            if(i == j)
            {
                continue;
            }
            if(sum == (numbers[i] + numbers[j]))
            {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    std::deque<long long> buffer;
    std::vector<long long> all_numbers;
    const int premable_size = 25;
    long long invalid;

    while(std::getline(file, s))
    {
        long long number = std::stoll(s);
        all_numbers.push_back(number);

        if(buffer.size() == premable_size)
        {
            if(!checkIfSum(number, buffer))
            {
                invalid = number;
                std::cout << "part 1: " << invalid << std::endl;
                break;
            }
        }
        buffer.push_back(number);
        if(buffer.size() > premable_size)
        {
            buffer.pop_front();
        }
    }
    // part 2
    // find sum of continuos number sequence that result in the invalid number
    for(int i=0; i < all_numbers.size(); ++i)
    {
        int sum = 0;
        std::vector<long long> numbers;
        for(int j=i; j < all_numbers.size(); ++j)
        {
            sum += all_numbers[j];
            numbers.push_back(all_numbers[j]);
            if(sum == invalid)
            {
                const auto pair = std::minmax_element(numbers.begin(), numbers.end());
                std::cout << "part 2: " << *pair.first + *pair.second << std::endl;
                return 0;
            }
        }
    }
    return 0;
}