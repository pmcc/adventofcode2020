#include <fstream>
#include <set>
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
    std::set<int> numbers;

    if (!input.is_open())
    {
        return 0;
    }

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
            int result = *found * current;
            std::cout << result << std::endl;
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
                    int result = first_number * second_number * third_number;
                    std::cout << result << std::endl;
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