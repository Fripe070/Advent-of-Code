# Advent of code 2021 day 2 part 1
# https://adventofcode.com/2021/day/2

with open("input.txt", "r") as f:
    horizontal = 0
    depth = 0
    for line in f.readlines():
        action = line.strip().split(" ")[0]
        amount = int(line.strip().split(" ")[1])

        if action == "up":
            depth -= amount
        elif action == "down":
            depth += amount
        elif action == "forward":
            horizontal += amount

print(f"""Final horizontal position: {horizontal}
Final depth: {depth}

{horizontal} * {depth} = {horizontal * depth}""")
