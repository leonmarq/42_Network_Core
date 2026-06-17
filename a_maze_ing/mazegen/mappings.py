from enum import Enum


class Direction(Enum):
    N = 0
    E = 1
    S = 2
    W = 3


OPPOSITE = {
    Direction.N: Direction.S,
    Direction.E: Direction.W,
    Direction.S: Direction.N,
    Direction.W: Direction.E,
}

OFFSETS = {
    Direction.N: (0, -1),
    Direction.E: (1, 0),
    Direction.S: (0, 1),
    Direction.W: (-1, 0),
}
