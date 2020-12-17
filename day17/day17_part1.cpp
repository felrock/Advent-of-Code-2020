#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <functional>

struct XYZ
{
    int x;
    int y;
    int z;
};

bool operator==(const XYZ& a, const XYZ& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// custom hash can be a standalone function object:
struct XYZHash 
{
    std::size_t operator()(XYZ const& xyz) const noexcept
    {
        // boost combine hases algo
        std::size_t h1 = std::hash<int>{}(xyz.x);
        std::size_t h2 = std::hash<int>{}(xyz.y);
        std::size_t h3 = std::hash<int>{}(xyz.z);
        std::size_t seed = h2 + 0x9e3779b9 + (h1<<6) + (h1>>2);
        seed ^= h3 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};

int countNeighbors(const XYZ& xyz, const std::unordered_set<XYZ, XYZHash>& world, const std::vector<XYZ>& neighbors)
{
    int count_neighbors = 0;
    for(const auto& n : neighbors)
    {
        XYZ txyz{xyz.x+n.x, xyz.y+n.y, xyz.z+n.z};
        if(world.find(txyz) != world.end())
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
    std::unordered_set<XYZ, XYZHash> world;
    int x=0, y=0, z=0;
    while(std::getline(file, s))
    {
        for(const auto& chr : s)
        {
            if(chr == '#')
            {
                world.insert(XYZ{x, y, z});
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
                    neighbors.push_back(XYZ{v1,v2,v3});
                }
            }
        }
    }
    // iterate world
    unsigned int iteration = 0;
    const unsigned int max_iterations = 6;
    while(iteration < max_iterations)
    {
        std::unordered_set<XYZ, XYZHash> new_world;
        for(const auto& xyz : world)
        {
            int count_neighbors = countNeighbors(xyz, world, neighbors);
            if(count_neighbors == 2 || count_neighbors == 3)
            {
                new_world.insert(xyz);
            }

            for(const auto& v : neighbors)
            {
                XYZ neighbor_pos{xyz.x+v.x, xyz.y+v.y, xyz.z+v.z};
                // found empty neighbor, and we havent added it as a neighbor before
                if(world.find(neighbor_pos) == world.end())
                {
                    int count_neighbor_neighbors = countNeighbors(neighbor_pos, world, neighbors);
                    if(count_neighbor_neighbors == 3)
                    {
                        new_world.insert(neighbor_pos);
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