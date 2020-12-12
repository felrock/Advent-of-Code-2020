#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

int main(int argc, char** argv)
{
    std::fstream file(argv[1]);
    std::string s;

    const double pi = std::acos(-1);
    int px = 0;
    int py = 0;
    int wx = 10;
    int wy = 1;
    int cos_val, sin_val, wxt;

    while(std::getline(file, s))
    {
        int value = std::stoi(s.substr(1, s.size()));
        switch (s[0])
        {
        case 'N':
            wy += value;
            break;
        case 'S':
            wy -= value;
            break;
        case 'E':
            wx += value;
            break;
        case 'W':
            wx -= value;
            break;
        case 'L':
            cos_val = std::cos((static_cast<double>(value)/180.0)*pi);
            sin_val = std::sin((static_cast<double>(value)/180.0)*pi);

            wxt = wx;
            // counter-clockwise rotate
            wx = wx*cos_val - wy*sin_val;
            wy = wy*cos_val + wxt*sin_val;
            break;
        case 'R':
            cos_val = std::cos((static_cast<double>(value)/180.0)*pi);
            sin_val = std::sin((static_cast<double>(value)/180.0)*pi);

            wxt = wx;
            // clockwise rotate
            wx = wx*cos_val + wy*sin_val;
            wy = wy*cos_val - wxt*sin_val;
            break;
        case 'F':
            px += wx * value;
            py += wy * value;
            break;
        default:
            break;
        }
    }
    std::cout << std::abs(px) + std::abs(py) << std::endl;

    return 0;
}