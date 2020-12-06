#include <fstream>
#include <vector>
#include <string>
#include <fmt/printf.h>
#include <numeric>
#include <ranges>
#include <ctre.hpp>
#include <filesystem>
#include <algorithm>
#include <span>

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    auto file_size = std::filesystem::file_size("input.txt");
    char* buffer = new char[file_size];
    input.read(buffer, file_size);

    std::span content{buffer, file_size};

    int yes = 0;
    int everyone = 0;

    // Get groups with regex
    for (auto match : ctre::range<"(([a-z]+)(\n[a-z]+)*)">(content))
    {
        std::vector<char> answers;
        std::ranges::copy(match.get<0>(), back_inserter(answers));

        int ppl = std::ranges::count(answers, '\n') + 1;

        // Remove newlines
        answers.erase(std::ranges::begin(std::ranges::remove(answers, '\n')), std::end(answers));

        // Remove duplicates
        std::ranges::sort(answers);
        std::vector<char> uniques;
        std::ranges::unique_copy(answers, back_inserter(uniques));

        for (auto c : uniques)
        {
            if (std::ranges::count(answers, c) == ppl)
            {
                ++everyone;
            }
        }

        yes += uniques.size();
    }

    fmt::print("{}\n", yes);
    fmt::print("{}\n", everyone);

    delete[] buffer;

    return 0;
}