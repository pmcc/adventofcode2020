#include <fstream>
#include <set>
#include <algorithm>
#include <string>
#include <fmt/printf.h>

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    std::set<int> numbers;
    for (std::string line; std::getline(input, line);)
    {
        numbers.emplace(std::stoi(line));
    }

    // Part 1

    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        int current = *it;
        auto found = std::find_if(std::next(it), numbers.end(), [current](int number)
        {
            if (current + number == 2020)
            {
                return true;
            }

            return false;
        });

        if (found != numbers.end())
        {
            fmt::print("{}\n", *found * current);
        }
    }

    // Part 2

    for (auto it = numbers.begin(), end = numbers.end(); it != end; ++it)
    {
        auto found = std::find_if(std::next(it), end, [it, end](int second_number)
        {
            int first_number = *it;

            auto sub_found = std::find_if(std::next(it, 2), end, [first_number, second_number](int third_number)
            {
                if (first_number + second_number + third_number == 2020)
                {
                    fmt::print("{}\n", first_number * second_number * third_number);
                    return true;
                }

                return false;
            });

            return sub_found != end;
        });

        if (found != end)
        {
            break;
        }
    }

    return 0;
}