#include <fstream>
#include <iostream>
#include <vector>

std::string nums2str(const std::vector<int> &numbers) {
    std::string str;
    for (const int n : numbers)
        str += (n == -1) ? "." : std::to_string(n);
    return str;
}

std::string load() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return {};
    }
    std::string line;
    std::getline(file, line);
    return line;
}

unsigned long long part1(const std::string &input) {
    std::vector<int> expanded;
    for (
        int i = 0; i <
        input.size() - (input.size() % 2 == 0);  // We skip the last character if it is empty space
        i++
    ) {
        const int block_index = i / 2;
        int num = input[i] - '0';
        expanded.reserve(expanded.size() + num);
        while (num--)
            expanded.push_back((i % 2 == 0) ? block_index : -1);
    }

    unsigned long long checksum = 0;
    unsigned long long blank_index = 0;
    for (auto back_index = expanded.size() - 1; back_index > 0; back_index--) {
        const int value = expanded[back_index];
        if (value == -1 || value == 0) // 0 Will not matter anyway
            continue;
        while (blank_index < back_index && expanded[blank_index] != -1)
            blank_index++;
        if (blank_index < back_index)
            expanded[blank_index] = 0;
        checksum += std::min(back_index, blank_index) * value;
    }
    return checksum;
}

unsigned long long part2(const std::string &input) {
    std::vector<int> block_sizes;
    block_sizes.reserve(input.size());
    for (const char c : input)
        block_sizes.push_back(c - '0');

    std::vector<int> blocks_buffer;
    for (
        int i = 0; i <
        input.size() - (input.size() % 2 == 0);  // We skip the last character if it is empty space
        i++
    ) {
        const int block_index = i / 2;
        int num = input[i] - '0';
        while (num--)
            blocks_buffer.push_back((i % 2 == 0) ? block_index : -1);
    }

    auto bf_block_start = blocks_buffer.size();
    for (int size_offset = static_cast<int>(block_sizes.size()) - 1; size_offset > 0; size_offset--) {
        const int block_size = block_sizes[size_offset];
        bf_block_start -= block_size;
        if (size_offset % 2 == 1)
            continue;

        // Find the first empty space in the buffer large enough to fit the block
        int hole_i = -1;
        for (int buffer_i = 0; buffer_i < bf_block_start; buffer_i++) {
            for (int k = 0; k < block_size; k++)
                if (blocks_buffer[buffer_i + k] != -1)
                    goto fail;
            hole_i = buffer_i;
            break;
            fail:;
        }
        if (hole_i == -1) continue;

        for (int j = 0; j < block_size; j++)
            blocks_buffer[hole_i + j] = size_offset/2;
        for (int j = 0; j < block_size; j++)
            blocks_buffer[bf_block_start+j] = -1;
    }
    // Easier to just do the checksum afterward
    unsigned long long checksum = 0;
    for (auto i = 0; i < blocks_buffer.size(); i++) {
        const int value = blocks_buffer[i];
        if (value == -1 || value == 0)
            continue;
        checksum += i * value;
    }

    return checksum;
}

int main() {
    const std::string input = load();

    const auto p1 = part1(input);
    std::cout << "Part 1: " << p1 << std::endl;

    const auto p2 = part2(input);
    std::cout << "Part 2: " << p2 << std::endl;

    return 0;
}
