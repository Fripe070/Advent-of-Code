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


fixed = []

for i, page_numbers in enumerate(all_updates):
    if all(
        page_numbers.index(first) < page_numbers.index(last)
        for first, last in rules
        if first in page_numbers and last in page_numbers
    ):
        continue

    for number in tuple(page_numbers):
        for first, last in rules:
            if first != number: continue
            if last not in page_numbers: continue
            if first == last: raise Exception(f"Invalid rule {first, last}")

            first_index = page_numbers.index(first)
            last_index = page_numbers.index(last)

            if first_index > last_index:
                page_numbers.pop(first_index)
                page_numbers.insert(last_index, number)

    fixed.append(page_numbers)


summed = 0
for update in fixed:
    summed += update[(len(update)-1) // 2]

print(summed)

