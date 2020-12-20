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
    bool latest_op = true;
    for(int i=start; i < end; ++i)
    {
        if(str[i] == ' ')
        {
            //std::cout << "space cont" << std::endl;
            continue;
        }
        else if(str[i] == '(')
        {
            // find first ) after (A
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
            //std::cout << "left bracket goto " << i+1 << " " << new_end << std::endl;
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
            //std::cout << "+ latest op" << std::endl;
            latest_op = true;
        }
        else if(str[i] == '*')
        {
            //std::cout << "* latest op" << std::endl;
            latest_op = false;
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            int num = str[i] - '0';
            if(latest_op)
            {
                //std::cout << "+ with "<< num << std::endl;
                sum += num;
            }
            else
            {
                //std::cout << "* with "<< num << std::endl;
                sum *= num;
            }
        }
        //std::cout << "i " << i << " sum " << sum << std::endl;
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