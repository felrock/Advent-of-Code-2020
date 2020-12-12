#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    const std::vector<std::pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

    int px = 0;
    int py = 0;

    int dir_index = 0;
    std::pair<int, int> facing = dirs[0];

    while(std::getline(file, s))
    {
        int value = std::stoi(s.substr(1, s.size()));
        switch (s[0])
        {
        case 'N':
            py += value;
            break;
        case 'S':
            py -= value;
            break;
        case 'E':
            px += value;
            break;
        case 'W':
            px -= value;
            break;
        case 'L':
            // positive modulo
            dir_index = ((dir_index - (value / 90)) % 4 + 4) % 4;
            facing = dirs[dir_index];
            break;
        case 'R':
            dir_index = (dir_index + (value / 90)) % 4;
            facing = dirs[dir_index];
            break;
        case 'F':
            px += facing.first * value;
            py += facing.second * value;
            break;
        default:
            break;
        }
    }
    std::cout << std::abs(px) + std::abs(py) << std::endl;

    return 0;
}