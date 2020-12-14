#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<int> getIntervals(std::string str)
{
    std::stringstream ss;
    std::vector<int> numbers;
    for(const auto& chr : str)
    {
        if(chr == ',' && ss.str() != "")
        {
            numbers.push_back(std::stoi(ss.str()));
            ss.str("");
        }
        else if(chr != 'x' && chr != ',')
        {
            ss << chr;
        }
    }
    numbers.push_back(std::stoi(ss.str()));
    return numbers;
}

std::vector<std::pair<int, int>> getInternvalsWithIndex(std::string str)
{
    std::stringstream ss;
    std::vector<std::pair<int, int>> numbers;
    int i=0;
    for(const auto& chr : str)
    {
        if(chr == ',' && ss.str() != "")
        {
            numbers.push_back(std::make_pair(i, std::stoi(ss.str())));
            ss.str("");
            i++;
        }
        else if(chr != 'x' && chr != ',')
        {
            ss << chr;
        }
        if(chr == 'x')
        {
            i++;
        }
    }
    numbers.push_back(std::make_pair(i, std::stoi(ss.str())));

    return numbers;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // parse
    std::getline(file, s);
    int id = std::stoi(s);
    std::getline(file, s);
    std::vector<int> intervals_p1 = getIntervals(s);


    // part 1
    int t_id = id;
    bool best_time_found = false;
    int bus_time_closest = -1;
    while(!best_time_found)
    {
        for(const auto& time : intervals_p1)
        {
            if(t_id % time == 0)
            {
                best_time_found = true;
                bus_time_closest = time;
            }
        }
        t_id++;
    }
    // subtract one, t_id++ is applied before while exit
    std::cout << "part 1: " << (t_id - id - 1)*bus_time_closest << std::endl;

    // part 2
    std::vector<std::pair<int, int>> intervals_p2 = getInternvalsWithIndex(s);
    int i = 0;
    unsigned long long step = 1;
    unsigned long long number = 1;
    while(i < intervals_p2.size()-1)
    {
        // the pattern we are looking for is (x + offset % interval == 0) where
        // two bus time interval matches with their module operation, after we 
        // find each set of two we can use that as "step" to the next potential
        // sequence.
        if((number + intervals_p2[i].first) % intervals_p2[i].second == 0 &&
           (number + intervals_p2[i+1].first) % intervals_p2[i+1].second == 0)
           {
                if(step == 1)
                {
                    step *= (intervals_p2[i].second*intervals_p2[i+1].second);
                }
                else
                {
                    step *= intervals_p2[i+1].second;
                }
                
                i++;
           }
        number += step;
    }
    std::cout << "part 2: " << number-step << std::endl;
    return 0;
}