#include "Field.h"

bool byr::checkIfValid(const std::string& entry)
{
    if(entry.size() != 4)
    {
        return false;
    }
    int value = std::stoi(entry);

    return value >= min && value <= max;
}

bool iyr::checkIfValid(const std::string& entry)
{
    if(entry.size() != 4)
    {
        return false;
    }
    int value = std::stoi(entry);

    return value >= min && value <= max;
}

bool eyr::checkIfValid(const std::string& entry)
{
    if(entry.size() != 4)
    {
        return false;
    }
    int value = std::stoi(entry);

    return value >= min && value <= max;
}

bool hgt::checkIfValid(const std::string& entry)
{
    if(entry.size() <= 2)
    {
        return false;
    }
    int value = std::stoi(entry.substr(0, entry.size()-2));
    if(entry.find("in") != std::string::npos)
    {
        return value >= min_in && value <= max_in;
    }
    else if(entry.find("cm") != std::string::npos)
    {
        return value >= min_cm && value <= max_cm;
    }
    else
    {
        return false;
    }
}

bool hcl::checkIfValid(const std::string& entry)
{
    if(entry[0] != '#' || entry.size() != 7)
    {
        return false;
    }
    std::string value = entry.substr(1, entry.size());
    for(const auto& chr : value)
    {
        if(chr >= '0' && chr <= '9')
        {
            continue;
        }
        else if(chr >= 'a' && chr <= 'f')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool ecl::checkIfValid(const std::string& entry)
{
    return eye_colors.find(entry) != eye_colors.end();
}

bool pid::checkIfValid(const std::string& entry)
{
    if(entry.size() != 9)
    {
        return false;
    }
    for(const auto& chr : entry)
    {
        if(chr < '0' && chr > '9')
        {
            return false;
        }
    }
    return true;
}
