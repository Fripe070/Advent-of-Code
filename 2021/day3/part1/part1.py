# Advent of code 2021 day 3 part 1
# https://adventofcode.com/2021/day/3

with open("input.txt", "r") as f:
    bits = [
        [int(bit) * 2 - 1 for bit in line.strip()]  # 0 becomes -1 and 1 stays as 1
        for line in f
    ]

newbits = [0] * len(bits[0])
for line in bits:
    for index, value in enumerate(line):
        newbits[index] += value

gamma = int("".join([str(int(bit > 0)) for bit in newbits]), 2)
epsilon = int("".join([str(int(bit < 0)) for bit in newbits]), 2)

print(f"Gamma rate: {gamma}")
print(f"Epsilon rate: {epsilon}")

final = gamma * epsilon

print(f"Power consumption of the submarine: {final}")
