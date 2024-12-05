from typing import cast

with open("input.txt") as file:
    rules_text, _, pages_text = file.read().strip().partition("\n\n")
    rules: list[tuple[int, int]] = [
        cast(tuple[int, int], tuple(map(int, rule.split("|", 1))))
        for rule in rules_text.split("\n")
    ]
    all_updates: list[list[int]] = [
        list(map(int, line.split(",")))
        for line in pages_text.split("\n")
    ]

print(sum(
    update[len(update) // 2]
    for update in all_updates
    if all(
        update.index(first) < update.index(last)
        for first, last in rules
        if first in update and last in update
    )
))
