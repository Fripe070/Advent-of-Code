from pprint import pprint


with open("input.txt") as f:
    data: list[list[str]] = [[*line] for line in f.read().splitlines()]
    checked: list[list[bool]] = [[False for _ in line] for line in data]

DIRS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def print_mask(mask: list[list[bool]]) -> None:
    for line in mask:
        print("".join(["#" if x else "." for x in line]))

def flood_fill(x: int, y: int, mask: list[list[bool]]) -> int:
    checked[y][x] = True
    mask[y][x] = True
    char = data[y][x]
    count = 1
    for dx, dy in DIRS:
        nx, ny = x + dx, y + dy
        if not (
            0 <= nx < len(data[y])
            and 0 <= ny < len(data)
            and data[ny][nx] == char
            and not checked[ny][nx]
        ):
            continue
        count += flood_fill(nx, ny, mask)
    return count

def count_edges(mask: list[list[bool]]) -> int:
    width = len(mask[0])
    height = len(mask)

    edges = 0
    for y in range(-1, height+1):
        for x in range(-1, width+1):
            ...

    return edges


def main():
    masks: list[tuple[int, list[list[bool]]]] = []

    for y in range(len(data)):
        for x in range(len(data[y])):
            if not checked[y][x]:
                mask = [[False]*len(line) for line in data]
                masks.append((flood_fill(x, y, mask), mask))

    # for mask in masks:
    #     print_mask(mask)
    #     print()

    summed = 0
    for mask in masks:
        summed += count_edges(mask) * sum(map(sum, mask))
    print(summed)

if __name__ == "__main__":
    main()
