from enum import Enum
import numpy as np


def close_wall(cell, direction):
    return cell | (1 << direction)


def open_wall(cell, direction):
    return cell & ~(1 << direction)


def is_wall_closed(cell, direction):
    return bool(cell & (1 << direction))


class Direction(Enum):
    N = 0
    E = 1
    S = 2
    W = 3


def read_config(file, key) -> str:
    value = None
    with open(file, "r") as f:
        for line in f:
            if line.startswith(key):
                value = line.split("=")[1].strip()
                break
    if value is None:
        raise ValueError(f"Missing required config key: {key}")
    return value


def write_maze(maze, width, height, exit, output):
    with open(output, "w") as f:
        print(maze, file=f)


if __name__ == "__main__":
    file = "test_config.txt"
    width = int(read_config(file, "WIDTH"))
    height = int(read_config(file, "HEIGHT"))
    exit = read_config(file, "EXIT")
    output = read_config(file, "OUTPUT_FILE")
    isperfect = read_config(file, "PERFECT")
    maze = np.chararray(width, height)
    write_maze(maze, width, height, exit, output)
