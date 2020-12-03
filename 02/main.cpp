#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

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

    std::vector<std::string> entries;

    for (std::string line; std::getline(input, line); )
    {
        entries.emplace_back(line);
    }

    int valid_passwords = 0;

    // Assuming input is well formatted :D

    for (const std::string& entry : entries)
    {
        std::string::size_type delimiter_pos = entry.find(": ");
        std::size_t range_pos = std::string::npos;

        int min = std::stoi(entry, &range_pos);
        int max  = std::atoi(entry.c_str() + range_pos + 1);
        char character = entry[delimiter_pos - 1];

        std::string password = entry.substr(delimiter_pos + 2);

        int result = std::count(password.begin(), password.end(), character);

        if (result >= min && result <= max)
        {
            ++valid_passwords;
        }
    }

    std::cout << valid_passwords << std::endl;

    return 0;
}