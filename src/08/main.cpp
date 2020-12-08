#include <ctre.hpp>
#include <fmt/printf.h>
#include <fstream>
#include <functional>
#include <ranges>
#include <numeric>
#include <string>
#include <tuple>

using instruction = std::tuple<std::string, int>;

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    std::vector<instruction> boot_code;
    for (std::string line; std::getline(input, line); )
    {
        auto m = ctre::match<"(\\w{3}) ([\\+\\-]\\d+)">(line);
        auto op = m.get<1>().to_string();
        auto v = m.get<2>().to_string();

        boot_code.push_back(std::make_tuple(op, std::stoi(v)));
    }

    // Part 1

    auto run = [](const auto &code)
    {
        std::vector<int> counter(code.size(), 0);

        int acc = 0;
        int offset = 0;
        while (offset >= 0 && offset < code.size())
        {
            if (counter[offset])
            {
                break;
            }

            ++counter[offset];

            auto [op, v] = code[offset];

            if (op == "acc")
            {
                acc += v;
                ++offset;
            }
            else if (op == "jmp")
            {
                offset += v;
            }
            else
            {
                ++offset;
            }
        }

        return std::make_tuple(acc, offset);
    };

    fmt::print("{}\n", std::get<0>(run(boot_code)));

    // Part 2

    for (int loop = 0; loop < boot_code.size(); ++loop)
    {
        // alter op
        std::string op = std::get<0>(boot_code[loop]);
        if (op == "jmp")
        {
            std::get<0>(boot_code[loop]) = "nop";
        }
        else if (op == "nop")
        {
            std::get<0>(boot_code[loop]) = "jmp";
        }

        auto [acc, offset] = run(boot_code);
        if (offset >= boot_code.size())
        {
            fmt::print("{}\n", acc);
            break;
        }

        // restore op
        std::get<0>(boot_code[loop]) = op;
    }

    return 0;
}