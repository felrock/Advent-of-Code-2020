#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <functional>

long long calculate(std::string str, int start, int end)
{
    long long sum = 0;
    std::string chunk = str.substr(start, end);

    bool latest_op = chunk.find('*') != std::string::npos ? true : false;
    for(int i=start; i < end; ++i)
    {
        if(str[i] == ' ')
        {
            continue;
        }
        else if(str[i] == '(')
        {
            int new_end = i+1;
            int open = 1;
            while(open != 0)
            {
                if(str[new_end] == '(')
                {
                    open++;
                }
                if(str[new_end] == ')')
                {
                    open--;
                }
                new_end++;
            }
            if(latest_op)
            {
                sum += calculate(str, i+1, new_end);
            }
            else
            {
                sum *= calculate(str, i+1, new_end);
            }
            i = new_end;
        }
        else if(str[i] == '+')
        {
            latest_op = true;
        }
        else if(str[i] == '*')
        {
            latest_op = false;
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            int num = str[i] - '0';
            if(latest_op)
            {
                sum += num;
            }
            else
            {
                sum *= num;
            }
        }
    }
    return sum;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // read 
    long long sum = 0;
    while(std::getline(file, s))
    {
        long long t =  calculate(s, 0, s.size());
        sum += t;
    }
    std::cout << sum << std::endl;
    return 0;
}