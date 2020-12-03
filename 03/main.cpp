#include <fstream>
#include <vector>
#include <iostream>
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

    // Part 1

    std::vector<std::string> map;
    for (std::string line; std::getline(input, line); )
    {
        map.emplace_back(line);
    }

    int width = map[0].size();
    int height = map.size();

    auto get_trees_on_slope = [&map, width, height](int x_step, int y_step)
    {
        int happy_little_trees = 0;

        for (int x = 0, y = 0; y < height; y += y_step)
        {
            if (map[y][x % width] == '#')
            {
                ++happy_little_trees;
            }

            x += x_step;
        }

        return happy_little_trees;
    };

    std::cout << get_trees_on_slope(3, 1) << std::endl;

    // Part 2

    int result = get_trees_on_slope(1, 1)
        * get_trees_on_slope(3, 1)
        * get_trees_on_slope(5, 1)
        * get_trees_on_slope(7, 1)
        * get_trees_on_slope(1, 2);

    std::cout << result << std::endl;

    return 0;
}
