import numpy as np
from numpy.typing import NDArray
from mazegen import Maze
from .assets import (
    MazeChar as MC,
    MAZE_COLORS, PATH_COLORS, RESET, ENTRY_COLOR, EXIT_COLOR
)


class Display:
    """Render a maze in the terminal with optional colors and path display."""
    def __init__(self, maze: Maze) -> None:
        self.maze = maze
        self.width = maze.width * 2 + 1
        self.height = maze.height * 2 + 1
        self.grid: NDArray[np.int_] = np.zeros(
            (self.width, self.height), dtype=str)
        self.path_visible = True
        self.maze_color = "\033[37m"
        self.mci = 0
        self.pci = 0

    def is_cell(self, x: int, y: int) -> bool:
        return x % 2 == 1 and y % 2 == 1

    def is_vertical(self, x: int, y: int) -> bool:
        return x % 2 == 0 and y % 2 == 1

    def is_HOR(self, x: int, y: int) -> bool:
        return x % 2 == 1 and y % 2 == 0

    def is_junction(self, x: int, y: int) -> bool:
        return x % 2 == 0 and y % 2 == 0

    def no_wall_at(self, x: int, y: int) -> bool:
        if x < 0 or x >= self.width:
            return True
        if y < 0 or y >= self.height:
            return True
        return False

    def calculate_wall(self, x: int, y: int) -> str:
        up, down, left, right = True, True, True, True
        if (self.no_wall_at(x, y - 1)):
            up = False
        if (self.no_wall_at(x, y + 1)):
            down = False
        if (self.no_wall_at(x - 1, y)):
            left = False
        if (self.no_wall_at(x + 1, y)):
            right = False
        if (up and down and left and right):
            return MC.CROSS.value
        elif (up and down and left):
            return MC.T_LEFT.value
        elif (up and down and right):
            return MC.T_RIGHT.value
        elif (up and left and right):
            return MC.T_UP.value
        elif (down and left and right):
            return MC.T_DOWN.value
        elif (up and down):
            return MC.VERTICAL.value
        elif (left and right):
            return MC.HOR.value
        elif (up and right):
            return MC.BOT_LEFT.value
        elif (up and left):
            return MC.BOT_RIGHT.value
        elif (down and right):
            return MC.TOP_LEFT.value
        elif (down and left):
            return MC.TOP_RIGHT.value
        else:
            return "?"

    def grid_init(self) -> None:
        for y in range(self.height):
            for x in range(self.width):
                if (self.is_cell(x, y)):
                    if (self.maze.entry == (x // 2, y // 2)):
                        self.grid[x][y] = MC.START.value
                    elif (self.maze.exit == (x // 2, y // 2)):
                        self.grid[x][y] = MC.END.value
                    elif self.maze.pathcells.__contains__((x // 2, y // 2)):
                        if self.path_visible:
                            self.grid[x][y] = MC.PATH.value
                        else:
                            self.grid[x][y] = MC.CELL.value
                    elif (self.maze.maze[x // 2][y // 2] == 0b1111):
                        self.grid[x][y] = MC.BLOCK.value
                    else:
                        self.grid[x][y] = MC.CELL.value
                elif (self.is_vertical(x, y)):
                    self.grid[x][y] = MC.VERTICAL.value
                elif (self.is_HOR(x, y)):
                    self.grid[x][y] = MC.HOR.value
                elif (self.is_junction(x, y)):
                    self.grid[x][y] = self.calculate_wall(x, y)

    def grid_open_walls(self) -> None:
        for x in range(self.maze.width):
            for y in range(self.maze.height):
                cell = self.maze.maze[x][y]
                if cell & 0b0001 == 0:  # N open
                    self.grid[x * 2 + 1][y * 2] = MC.CELL.value
                if cell & 0b0010 == 0:  # E open
                    self.grid[x * 2 + 2][y * 2 + 1] = MC.CELL.value
                if cell & 0b0100 == 0:  # S open
                    self.grid[x * 2 + 1][y * 2 + 2] = MC.CELL.value
                if cell & 0b1000 == 0:  # W open
                    self.grid[x * 2][y * 2 + 1] = MC.CELL.value

    def recalc_junc(self, x: int, y: int) -> None:
        up = y > 0 and self.grid[x][y - 1] != MC.CELL.value
        down = y < self.height - 1 and self.grid[x][y + 1] != MC.CELL.value
        left = x > 0 and self.grid[x - 1][y] != MC.CELL.value
        right = x < self.width - 1 and self.grid[x + 1][y] != MC.CELL.value
        if (up and down and left and right):
            self.grid[x][y] = MC.CROSS.value
        elif (up and down and left):
            self.grid[x][y] = MC.T_LEFT.value
        elif (up and down and right):
            self.grid[x][y] = MC.T_RIGHT.value
        elif (up and left and right):
            self.grid[x][y] = MC.T_UP.value
        elif (down and left and right):
            self.grid[x][y] = MC.T_DOWN.value
        elif (up and down):
            self.grid[x][y] = MC.VERTICAL.value
        elif (left and right):
            self.grid[x][y] = MC.HOR.value
        elif (up and right):
            self.grid[x][y] = MC.BOT_LEFT.value
        elif (up and left):
            self.grid[x][y] = MC.BOT_RIGHT.value
        elif (down and right):
            self.grid[x][y] = MC.TOP_LEFT.value
        elif (down and left):
            self.grid[x][y] = MC.TOP_RIGHT.value
        elif (up or down or left or right):
            if up or down:
                self.grid[x][y] = MC.VERTICAL.value
            else:
                self.grid[x][y] = MC.HOR.value
        else:
            self.grid[x][y] = "?"

    def remove_stumps(self) -> None:
        for x in range(0, self.width):
            for y in range(0, self.height):
                if (self.is_junction(x, y)):
                    self.recalc_junc(x, y)

    def toggle_path(self) -> None:
        if not self.path_visible:
            self.path_visible = True
        else:
            self.path_visible = False

    def colorize(self, color: str, char: str) -> str:
        return f"{color}{char}{RESET}"

    def get_colored_char(self) -> dict[str, str]:
        maze_color = MAZE_COLORS[self.mci % len(MAZE_COLORS)]
        path_color = PATH_COLORS[self.pci % len(PATH_COLORS)]

        return {
            MC.CELL.value: self.colorize(maze_color, MC.CELL.value),
            MC.START.value: self.colorize(ENTRY_COLOR, MC.START.value),
            MC.END.value: self.colorize(EXIT_COLOR, MC.END.value),
            MC.PATH.value: self.colorize(path_color, MC.PATH.value),
            MC.VERTICAL.value: self.colorize(maze_color, MC.VERTICAL.value),
            MC.HOR.value: self.colorize(maze_color, MC.HOR.value),
            MC.TOP_LEFT.value: self.colorize(maze_color, MC.TOP_LEFT.value),
            MC.TOP_RIGHT.value: self.colorize(maze_color, MC.TOP_RIGHT.value),
            MC.BOT_LEFT.value: self.colorize(maze_color, MC.BOT_LEFT.value),
            MC.BOT_RIGHT.value: self.colorize(maze_color, MC.BOT_RIGHT.value),
            MC.T_LEFT.value: self.colorize(maze_color, MC.T_LEFT.value),
            MC.T_RIGHT.value: self.colorize(maze_color, MC.T_RIGHT.value),
            MC.T_UP.value: self.colorize(maze_color, MC.T_UP.value),
            MC.T_DOWN.value: self.colorize(maze_color, MC.T_DOWN.value),
            MC.CROSS.value: self.colorize(maze_color, MC.CROSS.value),
            MC.BLOCK.value: self.colorize(maze_color, MC.BLOCK.value),
        }

    def rotate_colors(self) -> None:
        self.mci = (self.mci + 1) % len(MAZE_COLORS)
        self.pci = (self.pci + 1) % len(PATH_COLORS)

    def render(self) -> None:
        self.grid_init()
        self.grid_open_walls()
        self.remove_stumps()

        colored_chars = self.get_colored_char()

        out = []
        for y in range(self.height):
            out.append("".join(
                colored_chars[self.grid[x][y]] for x in range(self.width)))
        for line in out:
            print(line)
