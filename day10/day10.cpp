#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // start with smallest adapter
    std::vector<int> adapters = {0};

    while(std::getline(file, s))
    {
        int adapter = std::stoi(s);
        adapters.push_back(adapter);
    }
    std::sort(adapters.begin(), adapters.end());

    int built_in_adapter = adapters[adapters.size()-1] + 3;
    // add the largest adapter
    adapters.push_back(built_in_adapter);

    // part 1
    int diff_one = 0;
    int diff_three = 0;
    for(int i=0; i < adapters.size()-1; ++i)
    {
        int diff = adapters[i+1] - adapters[i];
        if(diff == 3)
        {
            ++diff_three;
        }
        else if(diff == 1)
        {
            ++diff_one;
        }
    }
    std::cout << "part 1: " << diff_one * diff_three << std::endl;
    
    std::unordered_map<int, long long> paths;
    // add the first cases to avoid checking bounds
    paths[adapters.size()-1] = 1;
    paths[adapters.size()-2] = 1;
    paths[adapters.size()-3] = 1;
    // we will have atleast one connection
    long long connections = 1;

    // start from the back, skip iterating first cases
    for(int i=adapters.size()-4; i >= 0; --i)
    {
        int adapter_reach = adapters[i] + 3;

        if(adapter_reach >= adapters[i + 2])
        {
            connections += paths[i + 2];
        }
        if(adapter_reach >= adapters[i + 3])
        {
            connections += paths[i + 3];
        }
        // add current connections for memoization
        paths[i] = connections;
    }
    std::cout << "part 2: " << connections << std::endl;
}