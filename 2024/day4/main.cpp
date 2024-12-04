#include <fstream>
#include <iostream>
#include <vector>

#define SAFE_GET(grid, x, y) (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size() ? grid[y][x] : ' ')

std::vector<std::vector<char>> get_grid() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return {};
    }

    std::vector<std::vector<char>> grid;
    {
        std::string line;
        while (std::getline(file, line))
            grid.emplace_back(line.begin(), line.end());
    }
    return grid;
}

int part1(const std::vector<std::vector<char>> &grid) {
    int find_count = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] != 'X') continue;

            for (
                const auto [dx, dy]
                : {std::pair{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}
            ) {
#define SEARCH_STR "XMAS"
                char line[sizeof(SEARCH_STR)-1];
                for (int i = 0; i < sizeof(SEARCH_STR)-1; i++)
                    line[i] = SAFE_GET(grid, x + i * dx, y + i * dy);

                if (std::string(line, sizeof(SEARCH_STR)-1) == SEARCH_STR)
                    find_count++;
#undef SEARCH_STR
            }
        }
    }
    return find_count;
}

int part2(const std::vector<std::vector<char>> &grid) {
    int find_count = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            const std::string possible[2] = {"MAS", "SAM"};

#define GET_LINE(dx, dy) std::string(1, SAFE_GET(grid, x-dx, y-dy)) \
            +SAFE_GET(grid, x, y) \
            +SAFE_GET(grid, x+dx, y+dy)

            const auto diag_down = GET_LINE(1, 1);
            const auto diag_up = GET_LINE(1, -1);
            if (
                (diag_down == possible[0] || diag_down == possible[1])
                && (diag_up == possible[0] || diag_up == possible[1])
            )
                find_count++;
        }
    }

    return find_count;
}

int main() {
    const auto grid = get_grid();

    const int p1 = part1(grid);
    std::cout << "Part 1: " << p1 << std::endl;
    const int p2 = part2(grid);
    std::cout << "Part 2: " << p2 << std::endl;

    return 0;
}

