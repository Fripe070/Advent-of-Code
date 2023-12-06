from enum import Enum, auto


class Cube(Enum):
    RED = auto()
    GREEN = auto()
    BLUE = auto()


with open("input.txt") as file:
    lines = [
        line.removeprefix("Game ")
        for line in file.read().splitlines()
    ]


def extract_counts(pairing: str) -> dict[Cube, int]:
    data = {}
    for pair in pairing.split(", "):
        count, cube_color = pair.split(" ")
        data[Cube[cube_color.upper()]] = int(count)
    return data


games: dict[int, list[dict[Cube, int]]] = {
    int((game := line.split(": "))[0].removeprefix("Game ")): list(map(extract_counts, game[1].split("; ")))
    for line in lines
}

def min_to_be_possible(game: list[dict[Cube, int]]) -> dict[Cube, int]:
    required = {
        Cube.RED: 0,
        Cube.GREEN: 0,
        Cube.BLUE: 0,
    }
    for pairing in game:
        for cube_color, count in pairing.items():
            if count > required[cube_color]:
                required[cube_color] = count
    return required

def mult(*values: int) -> int:
    result = 1
    for value in values:
        result *= value
    return result


required_game_powers: list[int] = []
for game_id, game in games.items():
    required_game_powers.append(mult(*min_to_be_possible(game).values()))

print(sum(required_game_powers))

