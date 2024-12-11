def apply_rule(n: int) -> list[int]:
    if n == 0:
        return [1]
    if len(str(n)) % 2 == 0:
        str_n = str(n)
        return [
            int(str_n[:len(str_n)//2]),
            int(str_n[len(str_n)//2:]),
        ]
    return [n*2024]


def main():
    with open("input.txt") as file:
        stones = map(int, file.read().split(" "))

    for i in range(25):
        new_stones = []
        for stone in stones:
            new_stones.extend(apply_rule(stone))
        stones = new_stones
        print(i, len(stones))


if __name__ == "__main__":
    main()
