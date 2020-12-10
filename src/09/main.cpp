#include <fmt/printf.h>
#include <fstream>
#include <functional>
#include <ranges>
#include <numeric>
#include <string>
#include <algorithm>

// not optimal but whatever
template <typename T, int size>
class matrix
{
public:
    explicit matrix(const std::vector<T>& params)
    {
        generate(params);
    }

    void shift_input(T v)
    {
        // Shift params and append new value
        std::vector<T> params(size);
        for (int i = 1; i < size; ++i)
        {
            params[i - 1] = _data[i + i * size] >> 1;
        }
        params[size - 1] = v;
        generate(params);
    }

    bool contains(T v)
    {
        return std::ranges::find(_data, v) != _data.end();
    }

private:
    void generate(const std::vector<T>& params)
    {
        for (int row = 0; row < size; ++row)
        {
            int v1 = params[row % size];
            for (int col = 0; col < size; ++col)
            {
                _data[col + row * size] = v1 + params[col % size];
            }
        }
    }

private:
    std::array<T, size * size> _data;
};

int main(int argc, char** argv)
{
    std::ifstream input("input.txt");

    if (!input.is_open())
    {
        return 0;
    }

    std::vector<long long> numbers;
    std::ranges::copy(std::ranges::istream_view<std::string>(input) | std::views::transform([](const std::string& v) { return std::stoll(v); }), std::back_inserter(numbers));

    // Part 1

    matrix<long long, 25> mat(numbers);
    auto r = numbers | std::views::drop(25);
    auto found = std::ranges::find_if(r,
        [&mat](long long v)
        {
            if (!mat.contains(v))
            {
                return true;
            }

            mat.shift_input(v);
            return false;
        }
    );

    if (found != numbers.end())
    {
        long long part1 = *found;
        fmt::print("{}\n", part1);

        // Part 2

        // not optimal but whatever
        for (int i = 0; i < numbers.size(); ++i)
        {
            int sum = numbers[i];
            for (int y = i + 1; y < numbers.size() - 1; ++y)
            {
                sum += numbers[y];
                if (sum > part1)
                {
                    continue;
                }
                else if (sum == part1)
                {
                    auto [min, max] = std::ranges::minmax(numbers | std::views::drop(i) | std::views::take(y - i));
                    fmt::print("{}\n", min + max);
                    return 0;
                }
            }
        }
    }

    return 0;
}
