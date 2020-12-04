#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <optional>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return 0;
    }

    std::ifstream input(argv[1]);

    if (!input.is_open())
    {
        return 0;
    }

    std::vector<std::string> passports;
    std::string passport_data;
    for (std::string line; std::getline(input, line); )
    {
        if (line.empty())
        {
            passports.push_back(passport_data);
            passport_data.clear();
        }
        else
        {
            passport_data.append(line);
            passport_data.append(" ");
        }
    }

    if (!passport_data.empty())
    {
        passports.push_back(passport_data);
    }

    constexpr auto required_fields =
    {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid",
    };

    int valid_passports = 0;

    for (const std::string& passport : passports)
    {
        int fields = 0;
        for (const auto& field : required_fields)
        {
            if (passport.find(field) != std::string::npos)
            {
                ++fields;
            }
        }

        valid_passports += (fields == std::size(required_fields));
    }

    std::cout << valid_passports << std::endl;

    return 0;
}