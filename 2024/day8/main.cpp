#include <fstream>
#include <iostream>
#include <ranges>
#include <future>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"

void print_grid(
    const std::unordered_map<char, std::vector<glm::ivec2>> &antennas,
    const std::vector<glm::ivec2> &antinodes,
    const glm::ivec2 bounds
) {
    for (int y = 0; y < bounds.y; y++) {
        for (int x = 0; x < bounds.x; x++) {
            glm::ivec2 pos = {x, y};
            for (auto [c, ant]: antennas) {
                if (auto it = std::ranges::find(ant, pos); it != ant.end()) {
                    std::cout << c;
                    goto next;
                }
            }
            if (auto it = std::ranges::find(antinodes, pos); it != antinodes.end()) {
                std::cout << '#';
                continue;
            }
            std::cout << '.';
            next:;
        }
        std::cout << std::endl;
    }
}

std::pair<std::unordered_map<char, std::vector<glm::ivec2>>, glm::ivec2> load() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return {};
    }

    std::unordered_map<char, std::vector<glm::ivec2>> antennas;
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < line.size(); x++)
            if (char c = line[x]; c != '.') antennas[c].push_back({x, y});
        y++;
    }

    return std::pair(antennas, glm::ivec2{y, y});
}

std::vector<glm::ivec2> part1(const std::unordered_map<char, std::vector<glm::ivec2>> &allAntennas, const glm::ivec2 bounds) {
    std::vector<glm::ivec2> antinodes;
#define IN_BOUNDS(pos) (pos.x >= 0 && pos.y >= 0 && pos.x < bounds.x && pos.y < bounds.y)
#define IN_BOUNDS_UNIQUE(pos) (IN_BOUNDS(pos) && std::ranges::find(antinodes, pos) == antinodes.end())

    for (std::vector antennas: allAntennas | std::views::values) {
        for (glm::ivec2 antenna: antennas) {
            for (glm::ivec2 otherAntenna: antennas) {
                if (antenna == otherAntenna) continue;
                glm::ivec2 toOther = otherAntenna - antenna;

                if (glm::ivec2 pos1 = antenna - toOther;        IN_BOUNDS_UNIQUE(pos1)) antinodes.push_back(pos1);
                if (glm::ivec2 pos2 = otherAntenna + toOther;   IN_BOUNDS_UNIQUE(pos2)) antinodes.push_back(pos2);
            }
        }
    }
#undef IN_BOUNDS
#undef IN_BOUNDS_UNIQUE

    return antinodes;
}

std::vector<glm::ivec2> part2(const std::unordered_map<char, std::vector<glm::ivec2>> &allAntennas, const glm::ivec2 bounds) {
    std::vector<glm::ivec2> antinodes;
#define IN_BOUNDS(pos) (pos.x >= 0 && pos.y >= 0 && pos.x < bounds.x && pos.y < bounds.y)
#define UNIQUE(pos) (std::ranges::find(antinodes, pos) == antinodes.end())

    for (std::vector antennas: allAntennas | std::views::values) {
        for (glm::ivec2 antenna: antennas) {
            for (glm::ivec2 otherAntenna: antennas) {
                if (antenna == otherAntenna) continue;
                glm::ivec2 toOther = otherAntenna - antenna;

                glm::ivec2 pos = antenna;
                while (pos = pos + toOther, IN_BOUNDS(pos)) {
                    if (UNIQUE(pos)) antinodes.push_back(pos);
                }
                pos = otherAntenna;
                while (pos = pos - toOther, IN_BOUNDS(pos)) {
                    if (UNIQUE(pos)) antinodes.push_back(pos);
                }
            }
        }
    }
#undef IN_BOUNDS
#undef UNIQUE

    return antinodes;
}


int main() {
    const auto [antennas, bounds] = load();

    const auto p1 = part1(antennas, bounds);
    std::cout << "Part 1: " << p1.size() << std::endl;

    const auto p2 = part2(antennas, bounds);
    std::cout << "Part 2: " << p2.size() << std::endl;

    return 0;
}

