#include <fstream>
#include <vector>
#include <string>
#include <fmt/printf.h>
#include <numeric>
#include <ranges>
#include <set>

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    // Part 1

    constexpr auto to_boarding_pass_id = [](std::string_view view)
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

    // Input stream is consumed so we copy the range to a vector in order to re-use the data
    std::vector<int> boarding_passes;
    std::ranges::copy(std::ranges::istream_view<std::string>(input) | std::views::transform(to_boarding_pass_id), std::back_inserter(boarding_passes));

    // Part 1

    fmt::print("{}\n", std::ranges::max(boarding_passes));

    // Part 2

    std::ranges::sort(boarding_passes);
    auto [min, max] = std::ranges::minmax(boarding_passes);

    std::vector<int> diff;
    std::ranges::set_difference(std::views::iota(min, max + 1), boarding_passes, back_inserter(diff));
    fmt::print("{}\n", diff.front());

    return 0;
}