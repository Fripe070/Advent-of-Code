# Advent of code 2021 day 1 part 2
# https://adventofcode.com/2021/day/1#part2

with open('input.txt', 'r') as f:
    lines = [int(line) for line in f.readlines()]

    old_sum = 0
    increase_times = 0

    for i in range(len(lines) - 2):
        depth_sum = lines[i] + lines[i+1] + lines[i+2]
        if old_sum and depth_sum > old_sum:
            increase_times += 1
        old_sum = depth_sum

print(f'Total increase times: {increase_times}')
