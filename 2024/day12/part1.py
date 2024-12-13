with open("input.txt") as f:
    data: list[list[str]] = [[*line] for line in f.read().splitlines()]
    checked: list[list[bool]] = [[False for _ in line] for line in data]

DIRS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def flood_fill(x: int, y: int) -> tuple[int, int]:
    count = 1
    edges = 0
    checked[y][x] = True
    char = data[y][x]
    for dx, dy in DIRS:
        nx, ny = x + dx, y + dy
        if not (
            0 <= nx < len(data[y])
            and 0 <= ny < len(data)
            and data[ny][nx] == char
        ):
            edges += 1
            continue
        if checked[ny][nx]:
            continue

        _count, _edges = flood_fill(nx, ny)
        count += _count
        edges += _edges
    return count, edges


def main():
    summed = 0
    for y in range(len(data)):
        for x in range(len(data[y])):
            if not checked[y][x]:
                count, edges = flood_fill(x, y)
                summed += count * edges

    print(summed)

if __name__ == "__main__":
    main()
