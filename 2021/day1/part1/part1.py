# Advent of code 2021 day 1 part 1
# https://adventofcode.com/2021/day/1

with open('input.txt', 'r') as f:
    increase_times = 0
    old_depth = 0
    for depth in f.readlines():
        if old_depth and int(depth) > old_depth:
            increase_times += 1
        old_depth = int(depth)

print(f'Total increase times: {increase_times}')
