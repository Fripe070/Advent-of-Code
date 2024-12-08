import operator
import itertools
from typing import Callable
from collections.abc import Sequence

with open("input.txt") as file:
    lines: list[tuple[int, list[int]]] = [
        (int(a), [*map(int, b.split(" "))])
        for a, _, b in map(lambda x:x.partition(": "), file.readlines())
    ]

def calculate(nums: list[int], ops: Sequence[Callable[[int, int], int]]) -> int:
    assert len(nums) == len(ops) + 1
    prev = nums[0]
    for i, n in enumerate(nums[1:]):
        prev = ops[i](prev, n)
    return prev

def main():
    summed = 0
    for test_value, nums in lines:
        ops: list[Callable[[int, int], int]] = [operator.add, operator.mul, lambda a, b: int(f"{a}{b}")]
        for comb in itertools.product(ops, repeat=len(nums)-1):
            calc = calculate(nums, comb)
            if calc == test_value:
                summed += calc
                break

    print(summed)


if __name__ == "__main__":
    main()
