from dataclasses import dataclass
from collections import namedtuple
from typing import cast

import numpy as np


Coord = namedtuple("Coord", ["x", "y"])


@dataclass
class Machine:
    a: Coord
    b: Coord
    prize: Coord

def parse_coord(text: str) -> Coord:
    x_index = text.index("X") + 2  # Really it is "X+" or "X="
    sep_index = text.index(", Y", x_index)
    return Coord(
        x=int(text[x_index:sep_index]),
        y=int(text[sep_index + 4:]),
    )

with open("input.txt") as f:
    machines: list[Machine] = []
    for machine in f.read().split("\n\n"):
        a, b, prize = machine.split("\n", maxsplit=2)
        machines.append(Machine(
            a=parse_coord(a),
            b=parse_coord(b),
            prize=parse_coord(prize)
        ))


costs: list[int] = []
for machine in machines:
    mat = np.array([
        [machine.a.x, machine.b.x*3],
        [machine.a.y, machine.b.y*3],
    ])
    prize = np.array([machine.prize.x, machine.prize.y])*3
    solution = np.linalg.solve(mat, prize)
    A_price = cast(float, solution[0])
    B_price = cast(float, solution[1])
    if A_price/3 > 100 or B_price > 100:
        continue
    if not round(A_price/3, 4).is_integer() or not round(B_price, 4).is_integer():
        continue
    total = round(A_price + B_price)
    costs.append(total)

print(sum(costs))


