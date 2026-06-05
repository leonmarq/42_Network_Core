from enum import Enum
import numpy as np


class Direction(Enum):
    O = 0
    N = 0
    E = 1
    S = 2
    W = 3


def read_config(file, key):
    with open(file, "r") as f:
        for line in f:
            if line.startswith(key):
                return line.split("=")[1].strip()
    return None


if __name__ == "__main__":
    file = "test_config.txt"
    width = read_config(file, "WIDTH")
    height = read_config(file, "HEIGHT")
    exit = read_config(file, "EXIT")
    output = read_config(file, "OUTPUT_FILE")
    isperfect = read_config(file, "PERFECT")
    data1 = np.random.random((width, height))

