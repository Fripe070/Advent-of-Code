from functools import cache


@cache
def resulting_counts_for(stone: int, iters_left: int) -> int:
    if iters_left == 0:
        return 1
    if stone == 0:
        return resulting_counts_for(1, iters_left - 1)
    if len(str(stone)) % 2 == 0:
        str_stone = str(stone)
        len_stone = len(str_stone)
        return (resulting_counts_for(int(str_stone[:len_stone//2]), iters_left - 1)
               +resulting_counts_for(int(str_stone[len_stone//2:]), iters_left - 1))
    return resulting_counts_for(stone*2024, iters_left - 1)

def main():
    with open("input.txt") as file:
        stones = map(int, file.read().split(" "))

    result = 0
    for stone in stones:
        result += resulting_counts_for(stone, 75)
    print(result)



if __name__ == "__main__":
    main()
