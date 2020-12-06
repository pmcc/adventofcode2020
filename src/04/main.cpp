#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <fmt/printf.h>
#include <ctre.hpp>
#include <string_view>

// Part 2

template <typename... Fs>
bool is_passport_valid(std::string_view view, Fs&&... validators)
{
    return (validators(view) && ...);
}

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

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

    // Part 1
    {
        const auto required_fields = 
        {
            "byr:",
            "iyr:",
            "eyr:",
            "hgt:",
            "hcl:",
            "ecl:",
            "pid:",
        };

        int valid_passports = 0;

        for (const std::string &passport : passports)
        {
            int fields = 0;
            for (const auto &field : required_fields)
            {
                if (passport.find(field) != std::string::npos)
                {
                    ++fields;
                }
            }

            valid_passports += (fields == required_fields.size());
        }

        fmt::print("{}\n", valid_passports);
    }

    // Part 2
    {
        auto byr = [](std::string_view view)
        {
            if (auto result = ctre::search<"byr:(\\d{4})\\s">(view))
            {
                int year = std::stoi(result.get<1>().to_string());
                return year >= 1920 && year <= 2002;
            }

            return false;
        };

        auto iyr = [](std::string_view view)
        {
            if (auto result = ctre::search<"iyr:(\\d{4})\\s">(view))
            {
                int year = std::stoi(result.get<1>().to_string());
                return year >= 2010 && year <= 2020;
            }

            return false;
        };

        auto eyr = [](std::string_view view)
        {
            if (auto result = ctre::search<"eyr:(\\d{4})\\s">(view))
            {
                int year = std::stoi(result.get<1>().to_string());
                return year >= 2020 && year <= 2030;
            }

            return false;
        };

        auto hgt = [](std::string_view view)
        {
            if (auto result = ctre::search<"hgt:(\\d{2,3})(cm|in)\\s">(view))
            {
                int height = std::stoi(result.get<1>().to_string());
                auto metric = result.get<2>().to_view();
                if (metric == "cm")
                {
                    return height >= 150 && height <= 193;
                }
                else if (metric == "in")
                {
                    return height >= 59 && height <= 76;
                }
            }

            return false;
        };

        auto hcl = [](std::string_view view)
        {
            return ctre::search<"hcl:#(\\d|[a-f]){6}\\s">(view);
        };

        auto ecl = [](std::string_view view)
        {
            return ctre::search<"ecl:(amb|blu|brn|gry|grn|hzl|oth)\\s">(view);
        };

        auto pid = [](std::string_view view)
        {
            return ctre::search<"pid:(\\d{9})\\s">(view);
        };

        int valid_passports = 0;

        for (const std::string &passport : passports)
        {
            valid_passports += is_passport_valid(
                passport,
                byr, iyr, eyr, hgt, hcl, ecl, pid
            );
        }

        fmt::print("{}\n", valid_passports);
    }

    return 0;
}
