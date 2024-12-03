print((
    func := lambda extracted, _, rest: sum(map(
        lambda t: int(t[0]) * int(t[1]),
        [x for x in __import__("re").findall(r"mul\((\d+),(\d+)\)", extracted)]
    )) + (func(*rest.partition("do()")[2].partition("don't()")) if rest else 0)
)(*open("input.txt").read().partition("don't()")))
