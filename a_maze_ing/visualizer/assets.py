from enum import Enum


class MazeChar(Enum):
    VERTICAL = "│"
    HOR = "─"

    TOP_LEFT = "┌"
    TOP_RIGHT = "┐"
    BOT_LEFT = "└"
    BOT_RIGHT = "┘"

    T_LEFT = "┤"
    T_RIGHT = "├"
    T_DOWN = "┬"
    T_UP = "┴"

    CROSS = "┼"

    BLOCK = "█"

    CELL = " "
    START = "E"
    END = "x"
    PATH = "o"


RESET = "\033[0m"

MAZE_COLORS = [
    "\033[97m",  # white
    "\033[96m",  # cyan
    "\033[93m",  # yellow
    "\033[92m",  # green
]

PATH_COLORS = [
    "\033[90m",  # gray
]

ENTRY_COLOR = "\033[95m"  # purple
EXIT_COLOR = "\033[91m"  # red

maze_color_index = 0
path_color_index = 0
