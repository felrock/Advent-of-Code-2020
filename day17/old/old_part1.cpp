#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <regex>
#include <unordered_map>

using XYZ = std::tuple<int, int, int>;

std::string xyzToString(const XYZ& xyz)
{
    return std::to_string(std::get<0>(xyz)) + "," + std::to_string(std::get<1>(xyz)) + "," + std::to_string(std::get<2>(xyz));
}

XYZ stringToXyz(const std::string& str)
{
    std::string s;
    std::vector<int> nums;
    for(const auto& chr : str)
    {
        if(chr == ',')
        {
            nums.push_back(std::stoi(s)); 
            s = "";
        }
        else
        {
            s += chr;
        }
    }
    return XYZ(nums[0], nums[1], nums[2]);
}

int countNeighbors(const XYZ& xyz, const std::unordered_map<std::string, XYZ>& world, const std::vector<XYZ>& neighbors)
{
    int count_neighbors = 0;
    int x1 = std::get<0>(xyz);
    int y1 = std::get<1>(xyz);
    int z1 = std::get<2>(xyz);

    for(const auto& n : neighbors)
    {
        XYZ txyz = std::make_tuple(x1+std::get<0>(n), y1+std::get<1>(n), z1+std::get<2>(n));
        if(world.find(xyzToString(txyz)) != world.end())
        {
            count_neighbors++;
        }
    }
    return count_neighbors;
}

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    // read 
    std::unordered_map<std::string, XYZ> world;
    int x=0, y=0, z=0;
    while(std::getline(file, s))
    {
        for(const auto& chr : s)
        {
            if(chr == '#')
            {
                XYZ xyz = std::make_tuple(x, y, z);
                world[xyzToString(xyz)] = xyz;
            }
            x++;
        }
        x = 0;
        y++;
    }
    // create neighbor positions
    const std::vector<int> val = {1, 0, -1};
    std::vector<XYZ> neighbors;
    for(const auto& v1 : val)
    {
        for(const auto& v2 : val)
        {
            for(const auto& v3 : val)
            {
                if(v1 != 0 || v2 != 0 || v3 != 0)
                {
                    neighbors.push_back(std::make_tuple(v1,v2,v3));
                }
            }
        }
    }
    // iterate world
    unsigned int iteration = 0;
    const unsigned int max_iterations = 6;
    while(iteration < max_iterations)
    {
        std::unordered_map<std::string, XYZ> new_world;
        for(const auto& xyz : world)
        {
            int count_neighbors = countNeighbors(xyz.second, world, neighbors);

            if(count_neighbors == 2 || count_neighbors == 3)
            {
                new_world[xyz.first] = xyz.second;
            }
            // see if anything should be added around current pos
            int x1 = std::get<0>(xyz.second);
            int y1 = std::get<1>(xyz.second);
            int z1 = std::get<2>(xyz.second);

            for(const auto& v : neighbors)
            {
                XYZ neighbor_pos = std::make_tuple(x1+std::get<0>(v), y1+std::get<1>(v), z1+std::get<2>(v));
                // found empty neighbor
                std::string neighbor_pos_str = xyzToString(neighbor_pos);

                if(world.find(neighbor_pos_str) == world.end())
                {
                    int count_neighbor_neighbors = countNeighbors(neighbor_pos, world, neighbors);
                    if(count_neighbor_neighbors == 3)
                    {
                        new_world[neighbor_pos_str] = neighbor_pos;
                    }
                }
            }
        }
        world = new_world;
        iteration++;
    }
    std::cout << world.size() << std::endl;
    return 0;
}