#include <fstream>
#include <iostream>
#include <ranges>
#include <future>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"


template <typename T>
using Grid2D = std::vector<std::vector<T>>;

constexpr glm::ivec2 directions[4] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
};
struct Guard {
    glm::ivec2 pos;
    int rot_i;

    void rotate(const int times = 1) {
        rot_i = (rot_i + times) % 4;
    }
    [[nodiscard]] char as_char() const {
        return "^>v<"[rot_i];
    }
};

#define OBSTACLE '#'
#define ESC "\033"

void print_grid(
    const Grid2D<bool> &grid,
    const Guard &guard,
    const std::unordered_map<glm::ivec2, int> &corner_rots = {},
    const std::vector<glm::ivec2> &highlight_positions = {}
) {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (guard.pos == glm::ivec2{x, y}) {
                std::cout << ESC"[1;31m" << guard.as_char() << ESC"[0m";
            } else if (corner_rots.contains(glm::ivec2{x, y})) {
                constexpr std::array corner_rot_chars = {"└", "┌", "┐", "┘",};
                std::cout << ESC"[1;35m" << corner_rot_chars[corner_rots.at(glm::ivec2{x, y})] << ESC"[0m";
            } else if (grid[y][x]) {
                std::cout << ESC"[1;34m" << OBSTACLE << ESC"[0m";
            } else if (highlight_positions.end() != std::ranges::find(highlight_positions, glm::ivec2{x, y})) {
                std::cout << ESC"[32;45m" << '.' << ESC"[0m";
            } else {
                std::cout << ESC"[1;32m" << '.' << ESC"[0m";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::pair<Grid2D<bool>, Guard> get_grid() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return {};
    }

    Guard guard = {{-1, -1}, -1};
    Grid2D<bool> grid;
    {
        std::string line;
        while (std::getline(file, line)) {
            grid.emplace_back();
            for (const char c: line) {
                grid.back().push_back(c == OBSTACLE);
                switch (c) {
#define CASE_ROT(c, rot) case c: guard = {{grid.back().size() - 1, grid.size() - 1}, rot}; break;
                    CASE_ROT('^', 0)
                    CASE_ROT('>', 1)
                    CASE_ROT('v', 2)
                    CASE_ROT('<', 3)
                    default: break;
                }
            }
        }
    }
    if (guard.pos == glm::ivec2{-1, -1})
        throw std::runtime_error("Guard not found");

    return {grid, guard};
}

#define OOB(g, pos) (pos.x < 0 || pos.y < 0 || pos.x >= g[0].size() || pos.y >= g.size())

int part1(const Grid2D<bool> &grid, Guard guard) {
    std::vector<glm::ivec2> visited_positions;
    while (true) {
        const glm::ivec2 new_pos = guard.pos + directions[guard.rot_i];
        if OOB(grid, new_pos) break;
        if (grid[new_pos.y][new_pos.x]) {
            guard.rotate();
            continue;
        }
        guard.pos = new_pos;
        if (std::ranges::find(visited_positions, guard.pos) == visited_positions.end())
            visited_positions.push_back(guard.pos);
    }

    return static_cast<int>(visited_positions.size()) + 1;
}

bool is_loop(const Grid2D<bool> &grid, Guard guard) {
    std::unordered_map<glm::ivec2, int> corner_rots; // Holds the rotations when *exiting* a corner

    while (true) {
        const glm::ivec2 new_pos = guard.pos + directions[guard.rot_i];
        if OOB(grid, new_pos) break;
        if (grid[new_pos.y][new_pos.x]) {
            guard.rotate();
            if (corner_rots.contains(guard.pos)) {
                if (corner_rots[guard.pos] == guard.rot_i)
                    return true;
            } else
                corner_rots[guard.pos] = guard.rot_i;
            continue;
        }
        guard.pos = new_pos;
    }

    return false;
}

int part2(const Grid2D<bool> &grid, Guard guard) {
    std::vector<std::future<int>> futures;
    futures.reserve(grid.size());
    for (int y = 0; y < grid.size(); ++y) {
        futures.push_back(std::async(std::launch::async, [y, &grid, guard] {
            int local_p2 = 0;
            const std::vector<bool> &row = grid[y];
            for (int x = 0; x < row.size(); ++x) {
                if (row[x]) continue;
                Grid2D<bool> local_grid = grid;
                local_grid[y][x] = true;
                if (is_loop(local_grid, guard))
                    local_p2++;
            }
            return local_p2;
        }));
    }

    int loops = 0;
    for (auto &fut : futures)
        loops += fut.get();
    return loops;
}

int main() {
    const auto [grid, guard] = get_grid();

    const int p1 = part1(grid, guard);
    std::cout << "Part 1: " << p1 << std::endl;
    assert(p1 == 5531);

    const int p2 = part2(grid, guard);
    std::cout << "Part 2: " << p2 << std::endl;

    return 0;
}

