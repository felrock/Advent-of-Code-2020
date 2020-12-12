#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
    walk in a given dx,dy on the grid until a occupied seat, empty seat or grid bounds.
*/
int walkInDirection(const std::vector<std::string>& grid,
                     const int& px, const int& dx,
                     const int& py, const int& dy,
                     const bool& runOnce)
{
    int tx = px + dx;
    int ty = py + dy;

    while(ty >= 0 && ty < grid.size() && tx >= 0 && tx < grid[0].size())
    {
        if(grid[ty][tx] == '#')
        {   
            return 1;
        }
        else if(grid[ty][tx] == 'L')
        {
            return 0;
        }
        if(runOnce)
        {
            return 0;
        }
        tx += dx;
        ty += dy;
    }
    return 0;
}

/*
    get all adjacemt seats, or if runOnce is false get all "visable" seats.
*/
int getOccupiedAdjacentSeats(const std::vector<std::string>& grid, const int& px, const int& py, const bool& runOnce)
{
    int occupied_seat_count = 0;

    occupied_seat_count += walkInDirection(grid, px,  0, py, -1, runOnce);
    occupied_seat_count += walkInDirection(grid, px,  1, py, -1, runOnce);
    occupied_seat_count += walkInDirection(grid, px,  1, py,  0, runOnce);
    occupied_seat_count += walkInDirection(grid, px,  1, py,  1, runOnce);
    occupied_seat_count += walkInDirection(grid, px,  0, py,  1, runOnce);
    occupied_seat_count += walkInDirection(grid, px, -1, py,  1, runOnce);
    occupied_seat_count += walkInDirection(grid, px, -1, py,  0, runOnce);
    occupied_seat_count += walkInDirection(grid, px, -1, py, -1, runOnce);

    return occupied_seat_count;
}
/*
    apply the rules for setting the current seat status.
*/
char applyRules(const std::vector<std::string>& grid, const int& px, const int& py, const bool& runOnce)
{
    char chr = grid[py][px];
    if(chr == '#')
    {
        int occupied_count = getOccupiedAdjacentSeats(grid, px, py, runOnce);
        int cmp_count = runOnce ? 4 : 5;
        if(occupied_count >= cmp_count)
        {
            return 'L';
        }
        else
        {
            return '#';
        }
    }
    else if(chr == 'L')
    {
        int occupied_count = getOccupiedAdjacentSeats(grid, px, py, runOnce);
        if(occupied_count == 0)
        {
            return '#';
        }
        else
        {
            return 'L';
        }
        
    }
    else
    {
        return '.';
    }  
}

bool isEqual(const std::vector<std::string>& a, const std::vector<std::string>& b)
{
    for(int i=0; i < a.size(); ++i)
    {
        if(a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // start with smallest adapter
    std::vector<std::string> ferry_seats_p1;
    std::vector<std::string> ferry_seats_p2;

    while(std::getline(file, s))
    {
        ferry_seats_p1.push_back(s);
        ferry_seats_p2.push_back(s);
    }
    // part 1
    std::vector<std::string> ferry_seats_cpy = ferry_seats_p1;
    bool stable_grid = false;
    while(!stable_grid)
    {
        for(int i=0; i < ferry_seats_p1.size(); ++i)
        {
           for(int j=0; j < ferry_seats_p1[0].size(); ++j)
           {
                ferry_seats_cpy[i][j] = applyRules(ferry_seats_p1, j, i, true);
           } 
        }
        if(isEqual(ferry_seats_p1, ferry_seats_cpy))
        {
            stable_grid = true;
        }
        // update state
        ferry_seats_p1 = ferry_seats_cpy;
    }
    int seat_count = 0;
    for(const auto& row : ferry_seats_p2)
    {
        seat_count += std::count(row.begin(), row.end(), '#');
    }
    std::cout << "part 1: " << seat_count << std::endl;

    // part 2
    ferry_seats_cpy = ferry_seats_p2;
    stable_grid = false;
    while(!stable_grid)
    {
        for(int i=0; i < ferry_seats_p2.size(); ++i)
        {
           for(int j=0; j < ferry_seats_p2[0].size(); ++j)
           {
                ferry_seats_cpy[i][j] = applyRules(ferry_seats_p2, j, i, false);
           } 
        }
        if(isEqual(ferry_seats_p2, ferry_seats_cpy))
        {
            stable_grid = true;
        }
        // update state
        ferry_seats_p2 = ferry_seats_cpy;
    }
    seat_count = 0;
    for(const auto& row : ferry_seats_p2)
    {
        seat_count += std::count(row.begin(), row.end(), '#');
    }
    std::cout << "part 2: " << seat_count << std::endl;
    return 0;
}