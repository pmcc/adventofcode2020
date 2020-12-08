#include <ctre.hpp>
#include <fmt/printf.h>
#include <fstream>
#include <functional>
#include <ranges>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <utility>

using node = std::pair<std::size_t, int>;
using nodes = std::vector<node>;
using graph = std::unordered_map<std::size_t, nodes>;

auto hash = [](std::string_view view) { return std::hash<std::string_view>{}(view); };

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    graph g;
    for (std::string line; std::getline(input, line); )
    {
        for (auto match : ctre::range<"([a-z ]+) bags contain (.*)">(line))
        {
            std::size_t start = hash(match.get<1>().to_view()); // container

            nodes nodes;
            for (auto containee : ctre::range<"(\\d+ )([a-z ]+) ">(match.get<2>().to_view()))
            {
                int weight = std::stoi(containee.get<1>().to_string());
                std::size_t end = hash(containee.get<2>().to_view());

                nodes.emplace_back(end, weight);
            }

            g.emplace(std::pair{ start, nodes });
        }
    }

    std::size_t to_find = hash("shiny gold");

    // Part 1

    auto part1 = [to_find](const graph& g)
    {
        auto unroll = [to_find](const graph& g, const nodes& n, const auto& self) -> bool
        {
            int i = 0;
            for (auto [k, w] : n)
            {
                if (k == to_find)
                {
                    ++i;
                }

                i += self(g, g.at(k), self);
            }

            return i;
        };

        int i = 0;
        for (auto [k, n] : g)
        {
            if (unroll(g, n, unroll))
            {
                ++i;
            }
        }

        return i;
    };

    fmt::print("{}\n", part1(g));

    // Part 2

    auto part2 = [to_find](const graph& g)
    {
        auto unroll = [](const graph& g, const nodes& n, const auto& self) -> int
        {
            int i = 1;
            for (auto [d, w] : n)
            {
                i += w * self(g, g.at(d), self);
            }

            return i;
        };

        return unroll(g, g.at(to_find), unroll);
    };

    fmt::print("{}\n", part2(g));

    return 0;
}