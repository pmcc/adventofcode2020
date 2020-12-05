#include <fstream>
#include <vector>
#include <string>
#include <fmt/printf.h>
#include <numeric>

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    // Part 1

    constexpr auto get_boarding_pass_id = [](std::string_view view)
    {
        int id = 0b1111111111;

        int offset = 0;
        for (auto it = view.rbegin(); it != view.rend(); ++it)
        {
            if (*it == 'F' || *it == 'L')
            {
                id &= ~(1 << offset);
            }
            

            ++offset;
        }

        return id;
    };

    std::vector<int> boarding_passes;
    for (std::string line; std::getline(input, line); )
    {
        boarding_passes.emplace_back(get_boarding_pass_id(line));
    }

    std::sort(boarding_passes.begin(), boarding_passes.end());

    fmt::print("{}\n", boarding_passes.back());

    // Part 2

    // Generate all ids between min & max
    std::vector<int> range(boarding_passes.back() - boarding_passes.front() + 1);
    std::iota(range.begin(), range.end(), boarding_passes.front());

    // Get the missing id
    int range_sum = std::accumulate(range.begin(), range.end(), 0);
    int sum = std::accumulate(boarding_passes.begin(), boarding_passes.end(), 0);
    int my_id = range_sum - sum;

    fmt::print("{}\n", my_id);

    return 0;
}