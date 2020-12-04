#ifndef day4_part2_h
#define day4_part2_h

#include <set>
#include <string>

class Field 
{
public:
    virtual ~Field()                                = default;
    virtual bool checkIfValid(const std::string& entry) = 0;
};

class byr : public Field
{
public:
    byr() = default;

private:
    bool checkIfValid(const std::string& entry) override;

    const int max = 2002;
    const int min = 1920;
};

class iyr : public Field
{
public:
    iyr() = default;
    
private:
    bool checkIfValid(const std::string& entry) override;

    const int max = 2020;
    const int min = 2010;
};

class eyr : public Field
{
public:
    eyr() = default;

private:
    bool checkIfValid(const std::string& entry) override;

    const int max = 2030;
    const int min = 2020;
};

class hgt : public Field
{
public:
    hgt() = default;
    
private:
    bool checkIfValid(const std::string& entry) override;

    const int max_cm = 193;
    const int min_cm = 150;
    const int max_in = 76;
    const int min_in = 59;
};

class hcl : public Field
{
public:
    hcl() = default;

private:
    bool checkIfValid(const std::string& entry) override;
};

class ecl : public Field
{
public:
    ecl() = default;

private:
    bool checkIfValid(const std::string& entry) override;

    const std::set<std::string> eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
};

class pid : public Field
{
public:
    pid() = default;

private:
    bool checkIfValid(const std::string& entry) override;
};

#endif