# Needed hint

from collections.abc import Iterable

def sign(n: int) -> int:
    """+1 if pos, 0 if 0, -1 if neg"""
    return (n>0) - (n<0)

def all_same(l: Iterable) -> bool:
    return len(set(l)) <= 1

with open("input.txt") as file:
    reports: list[list[int]] = [
        [int(n) for n in row.split(" ")]
        for row in file.read().splitlines()
    ]

def is_safe(report: list[int]) -> bool:
    # Last iter will be the original list
    for i in range(len(report)+1):
        excluded = report[:i] + report[i+1:]

        options = (sorted(excluded), sorted(excluded)[::-1])
        diffs = [a-b for a,b in zip(excluded[1:], excluded)]
        if (
            all_same(map(sign, diffs))
            and excluded in options
            and all(abs(diff) in {1,2,3} for diff in diffs)
        ):
            return True

    return False

safe = sum(is_safe(report) for report in reports)
print(safe)
