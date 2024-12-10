def ff(grid, x, y, n) -> set[tuple[int, int]]:
    ends_found = set()
    for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
        if not (0 <= (n_y := y+dy) < len(grid)): continue
        if not (0 <= (n_x := x+dx) < len(grid[n_y])): continue
        if grid[n_y][n_x] == n:
            if n == 9:
                ends_found.add((n_x, n_y))
            else:
                ends_found.update(ff(grid, n_x, n_y, n+1))
    return ends_found


def main():
    with open("input.txt") as file:
        grid: list[list[int]] = [
            [int(c) for c in l]
            for l in file.read().rstrip().splitlines()
        ]

    ends_found = 0
    for y in range(len(grid)):
        for x in range(len(grid[y])):
            num: int = grid[y][x]
            if num != 0: continue
            ends = ff(grid, x, y, 1)
            ends_found += len(ends)

    print(ends_found)


if __name__ == "__main__":
    main()
