#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    // read input
    std::fstream file("input.txt");
    std::string s;
    std::vector<std::string> input;
    while(std::getline(file, s))
    {
        input.push_back(s);
    }

    // part1 & part2
    const int height = input.size();
    const int width  = input[0].size();

    const std::vector<std::pair<int, int>> slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    int       part1 = 0;
    long long part2 = 1;

    for(const auto& pair: slopes)
    {
        int inc_x      = pair.first;
        int inc_y      = pair.second;
        int pos_x      = 0;
        int pos_y      = 0;
        int tree_count = 0;

        for(int i=pos_y; i < height; i += inc_y)
        {
            if(input[i][pos_x] == '#')
            {
                ++tree_count;
            }
            // wrap around
            pos_x = (inc_x + pos_x) % width;
        }
        // check if specific slope
        if(inc_x == 3 && inc_y == 1)
        {
            part1 = tree_count;
        }
        part2 *= tree_count;
    }
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
    return 0;
}