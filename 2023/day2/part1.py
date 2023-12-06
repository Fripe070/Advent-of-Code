import enum


class Cube(enum.Enum):
    RED = enum.auto()
    GREEN = enum.auto()
    BLUE = enum.auto()


contents = {
    Cube.RED: 12,
    Cube.GREEN: 13,
    Cube.BLUE: 14,
}


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

def is_game_possible(game: list[dict[Cube, int]]) -> bool:
    for pairing in game:
        for cube_color, count in pairing.items():
            if count > contents[cube_color]:
                return False
    return True

possible_games: list[int] = []
for game_id, game in games.items():
    if is_game_possible(game):
        possible_games.append(game_id)

print(sum(possible_games))

