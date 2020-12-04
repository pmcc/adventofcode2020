#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <fmt/printf.h>

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
                "byr",
                "iyr",
                "eyr",
                "hgt",
                "hcl",
                "ecl",
                "pid",
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
        auto byr_validation = [](const std::string& data)
        {
            int year = std::stoi(data);
            return year >= 1920 && year <= 2002;
        };

        auto iyr_validation = [](const std::string& data)
        {
            int year = std::stoi(data);
            return year >= 2010 && year <= 2020;
        };

        auto eyr_validation = [](const std::string& data)
        {
            int year = std::stoi(data);
            return year >= 2020 && year <= 2030;
        };

        auto hgt_validation = [](const std::string& data)
        {
            int height = std::stoi(data);
            if (data.find("cm") != std::string::npos)
            {
                return height >= 150 && height <= 193;
            }
            else if (data.find("in") != std::string::npos)
            {
                return height >= 59 && height <= 76;
            }

            return false;
        };

        auto hcl_validation = [](const std::string& data)
        {
            if (data.size() < 7 || data[0] != '#')
            {
                return false;
            }

            for (int i = 1; i < 7; ++i)
            {
                char c = data[i];
                if ((c < '0' || c > '9') && (c < 'a' || c > 'f'))
                {
                    return false;
                }
            }

            return true;
        };

        auto ecl_validation = [](std::string data)
        {
            const auto colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            for (const auto& color : colors)
            {
                if (data.find(color) != std::string::npos)
                {
                    return true;
                }
            }

            return false;
        };

        auto pid_validation = [](const std::string& data)
        {
            int valid = 0;
            auto start = data.begin();
            while (start != data.end() && *start >= '0' && *start <= '9')
            {
                ++valid;
                ++start;
            }

            return valid == 9;
        };

        struct field
        {
            std::string m_label;
            std::function<bool(const std::string&)> m_is_valid;
        };

        const field required_fields[] =
            {
                { "byr:", byr_validation },
                { "iyr:", iyr_validation },
                { "eyr:", eyr_validation },
                { "hgt:", hgt_validation },
                { "hcl:", hcl_validation },
                { "ecl:", ecl_validation },
                { "pid:", pid_validation },
            };

        int valid_passports = 0;

        for (const std::string &passport : passports)
        {
            int fields = 0;
            for (const auto &field : required_fields)
            {
                if (std::string::size_type offset = passport.find(field.m_label); offset != std::string::npos)
                {
                    fields += field.m_is_valid(passport.substr(offset + 4));
                }
            }

            valid_passports += (fields == sizeof(required_fields) / sizeof(required_fields[0]));
        }

        fmt::print("{}\n", valid_passports);
    }

    return 0;
}
