out = 0
rest = open("input.txt").read()
while rest:
    extracted, _, rest = rest.partition("don't()")
    # This is just the entire part 1 solution
    out += sum(map(
        lambda t: int(t[0]) * int(t[1]),
        [x for x in __import__("re").findall(r"mul\((\d+),(\d+)\)", extracted)]
    ))
    rest = rest.partition("do()")[2]
print(out)
