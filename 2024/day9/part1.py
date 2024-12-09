try:
    from tqdm import tqdm
except ImportError:
    def tqdm(iterable, *args, **kwargs):
        return iterable

with open("input.txt") as file:
    blocks = [int(c) for c in file.read().rstrip()]

expanded: list[int | None] = []
for i, n in enumerate(blocks):
    expanded.extend(
        ([i//2] * n)
        if i % 2 == 0 else
        ([None] * n)
    )

checksum = 0
try:
    for i in tqdm(range(len(expanded) - 1, 0, -1)):
        elem = expanded[i]
        if elem is None:
            continue
        empty_i = expanded.index(None)
        if empty_i < i:
            expanded[empty_i] = 0
        checksum += min(i, empty_i) * elem
except ValueError:
    pass

print(checksum)
