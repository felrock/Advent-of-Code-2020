#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <array>

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;
    std::vector<std::string> input;

    std::array<std::array<bool, 128>, 8> positions;

    // 
    for(auto& a : positions)
        for(auto& b : a)
             b = false;

    const char front = 'F';
    const char back = 'B';
    const char left = 'L';
    const char right = 'R';

    int max = 0;

    while(std::getline(file, s))
    {
        // parsing the input value
        int col = 0;
        int row = 0;

        int col_low = 0;
        int col_high = 7;
        int row_low = 0;
        int row_high = 127;

        char col_lst = ' ';
        char row_lst = ' ';

        for(const auto& chr : s)
        {
            if(chr == front)
            {
                int temp = (row_high - row_low) / 2 + 1;
                row_high -= temp;
                row_lst = chr;
            }
            else if(chr == back)
            {
                int temp = (row_high - row_low) / 2 + 1;
                row_low += temp;
                row_lst = chr;
            }
            else if(chr == right)
            {
                int temp = ((col_high - col_low) / 2) + 1;
                col_low += temp;
                col_lst = chr;
            }
            else if(chr == left)
            {
                int temp = ((col_high - col_low) / 2) + 1;
                col_high -= temp;
                col_lst = chr;
            }
        }
        // select number
        col = col_lst == left ? col_low : col_high;
        row = col_high == front ? row_high : row_low;

        positions[col][row] = true;

        int temp = (row * 8) + col;
        if(temp > max)
        {
            max = temp;
        }
    }
    std::cout << "part 1: " << max << std::endl;

    // find seat
    for(int i=1; i < positions[i].size()-1; ++i)
    {
        for(int j=1; j < positions.size()-1; ++j)
        {
            // all seats around this location are taken
            if(!positions[j][i] && positions[j+1][i] && positions[j][i+1] &&
                positions[j-1][i] && positions[j][i-1])
            {
                std::cout << "part 2: " << (i*8) + j << std::endl;
            }
        }
    }
    return 0;
}