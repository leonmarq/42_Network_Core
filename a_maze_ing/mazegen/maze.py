import random
import numpy as np
import time
from mazegen.mappings import OFFSETS, OPPOSITE, Direction
from numpy.typing import NDArray
from typing import Any
from pydantic import (
    BaseModel, Field, field_validator, model_validator, ValidationError
)


class MazeConfig(BaseModel):
    WIDTH: int = Field(..., ge=7)
    HEIGHT: int = Field(..., ge=7)
    ENTRY: tuple[int, int]
    EXIT: tuple[int, int]
    OUTPUT_FILE: str = Field("maze_output.txt")
    PERFECT: bool = Field(False)
    SEED: int | None = None

    @field_validator("ENTRY", "EXIT", mode="before")
    @classmethod
    def parse_tuple(cls, value: str, info: Any) -> tuple[int, int]:
        if isinstance(value, str):
            parts = value.split(",")
            if len(parts) != 2:
                raise ValueError(f"{info.field_name} must be in x,y format")
            try:
                x, y = map(int, parts)
            except ValueError:
                raise ValueError(f"{info.field_name} must be integers")
            return (x, y)
        return value

    @field_validator("WIDTH", "HEIGHT", mode="before")
    @classmethod
    def parse_dimension(cls, value: str, info: Any) -> int:
        try:
            return int(value)
        except (TypeError, ValueError):
            raise ValueError(f"{info.field_name} must be an integer")

    @model_validator(mode="after")
    def check_coordinates(self) -> "MazeConfig":
        if not (0 <= self.ENTRY[0] < self.WIDTH and
                0 <= self.ENTRY[1] < self.HEIGHT):
            raise ValueError("ENTRY coordinates must be within maze bounds")

        if not (0 <= self.EXIT[0] < self.WIDTH and
                0 <= self.EXIT[1] < self.HEIGHT):
            raise ValueError("EXIT coordinates must be within maze bounds")

        if self.ENTRY == self.EXIT:
            raise ValueError("ENTRY and EXIT cannot be the same")

        return self

    @field_validator("PERFECT", mode="before")
    def parse_perfect(cls, value: bool) -> bool:
        if isinstance(value, str):
            if value.lower() == "true":
                return True
            elif value.lower() == "false":
                return False
            else:
                raise ValueError("PERFECT must be 'True' or 'False'")
        return value


class Maze():
    """Generate, store, display, and export a maze.

    The maze is stored as a NumPy array of wall bitmasks. Each cell uses
    four bits for north, east, south, and west walls.
    """
    def __init__(
        self,
        width: int,
        height: int,
        entry: tuple[int, int],
        exit: tuple[int, int],
        perfect: bool,
        seed: int | None = None,
        output_file: str = "maze_output.txt"
    ) -> None:
        config = MazeConfig(
            WIDTH=width,
            HEIGHT=height,
            ENTRY=entry,
            EXIT=exit,
            PERFECT=perfect,
            SEED=seed,
            OUTPUT_FILE=output_file,
        )
        self._init_from_config(config)

    def _init_from_config(self, config: MazeConfig) -> None:
        self.width = config.WIDTH
        self.height = config.HEIGHT
        self.entry = config.ENTRY
        self.exit = config.EXIT
        self.perfect = config.PERFECT
        self.output_file = config.OUTPUT_FILE
        self.seed = config.SEED

        self.maze: NDArray[np.int_] = np.zeros(
            (self.width, self.height), dtype=np.int_)
        self.blocked: set[tuple[int, int]] = set()
        self.branch_cells: set[tuple[int, int]] = set()
        self.max_steps = self.width * self.height * 100
        self.path: list[Direction] = []
        self.pathcells: set[tuple[int, int]] = set()
        self.steps = 0

        self.generate()

    @classmethod
    def from_config(cls, config_file: str) -> "Maze":
        try:
            config_map = cls.read_config_file_into_dict(config_file)
            config = MazeConfig(**config_map)
            return cls._from_validated_config(config)
        except FileNotFoundError:
            raise ValueError(f"Error: Config file '{config_file}' not found")
        except ValidationError as e:
            first_error = e.errors()[0]
            if first_error["type"] == "missing":
                missing_key = first_error["loc"][0]
                raise ValueError(f"Error: missing required key {missing_key}")
            message = first_error["msg"]
            if message.startswith("Value error, "):
                message = message.removeprefix("Value error, ")
            raise ValueError(f"Error: {message}")
        except Exception as e:
            raise ValueError(f"Error: {e}")

    @classmethod
    def _from_validated_config(cls, config: MazeConfig) -> "Maze":
        maze = cls.__new__(cls)
        maze._init_from_config(config)
        return maze

    @staticmethod
    def read_config_file_into_dict(config_file: str) -> dict[str, Any]:
        config = {}
        with open(config_file, "r") as f:
            for line in f:
                if not line.strip() or line.startswith("#"):
                    continue
                if "=" not in line:
                    raise ValueError("invalid configuration line format")
                key, value = line.split("=", 1)

                if not key or not value:
                    raise ValueError("invalid configuration line format")
                config[key.strip()] = value.strip()
        return config

    def normalize_direction(self, direction: Direction) -> Direction:
        if isinstance(direction, Direction):
            return direction
        return Direction(direction)

    def get_array(self) -> NDArray[np.int_]:
        return self.maze

    def get_path(self) -> list[Direction]:
        return self.path

    def get_output_file(self) -> str:
        return self.output_file

    def init_pathcells(self) -> None:
        pos = self.entry
        for direction in self.path:
            self.pathcells.add(pos)
            pos = self.neighbor_pos(pos, direction)
        self.pathcells.add(pos)

    def is_in_bounds(self, pos: tuple[int, int]) -> bool:
        """Return whether a coordinate is inside the maze bounds."""
        x, y = pos
        return 0 <= x < self.width and 0 <= y < self.height

    def neighbor_pos(
        self,
        pos: tuple[int, int],
        direction: Direction
    ) -> tuple[int, int]:
        """Return the neighboring coordinate in the given direction."""
        x, y = pos
        dx, dy = OFFSETS[direction]
        return x + dx, y + dy

    def close_wall(
        self,
        pos: tuple[int, int],
        direction: Direction,
        mirror: bool = True
    ) -> None:
        direction = self.normalize_direction(direction)
        x, y = pos
        self.maze[x][y] |= 1 << direction.value
        neighbor = self.neighbor_pos(pos, direction)
        if mirror and self.is_in_bounds(neighbor):
            nx, ny = neighbor
            self.maze[nx][ny] |= 1 << OPPOSITE[direction].value

    def open_wall(
        self,
        pos: tuple[int, int],
        direction: Direction,
        mirror: bool = True
    ) -> None:
        direction = self.normalize_direction(direction)
        x, y = pos
        self.maze[x][y] &= ~(1 << direction.value)
        neighbor = self.neighbor_pos(pos, direction)
        if mirror and self.is_in_bounds(neighbor):
            nx, ny = neighbor
            self.maze[nx][ny] &= ~(1 << OPPOSITE[direction].value)

    def is_wall_closed(
        self,
        pos: tuple[int, int],
        direction: Direction
    ) -> bool:
        direction = self.normalize_direction(direction)
        x, y = pos
        return bool(self.maze[x][y] & (1 << direction.value))

    def boundary_direction(
        self,
        pos: tuple[int, int]
    ) -> Direction | None:
        x, y = pos
        if y == 0:
            return Direction.N
        if x == self.width - 1:
            return Direction.E
        if y == self.height - 1:
            return Direction.S
        if x == 0:
            return Direction.W
        return None

    def draw_42(self) -> None:
        midx = self.width // 2
        midy = self.height // 2
        cells = [
            (midx - 1, midy),
            (midx - 1, midy + 1),
            (midx - 1, midy + 2),
            (midx - 2, midy),
            (midx - 3, midy),
            (midx - 3, midy - 1),
            (midx - 3, midy - 2),
            (midx + 1, midy),
            (midx + 1, midy + 1),
            (midx + 1, midy + 2),
            (midx + 2, midy + 2),
            (midx + 2, midy),
            (midx + 3, midy),
            (midx + 3, midy + 2),
            (midx + 3, midy - 1),
            (midx + 3, midy - 2),
            (midx + 2, midy - 2),
            (midx + 1, midy - 2),
        ]
        for cell in cells:
            if self.entry == cell or self.exit == cell:
                raise ValueError("Entry or exit cannot be in the 42 pattern")
            if self.is_in_bounds(cell):
                x, y = cell
                self.maze[x][y] = 0b1111
                self.blocked.add(cell)

    def path_neighbor_count(
        self,
        pos: tuple[int, int],
        visited: set[tuple[int, int]]
    ) -> int:
        return sum(
            self.neighbor_pos(pos, direction) in visited
            for direction in Direction
        )

    def would_clump(
        self,
        pos: tuple[int, int],
        visited: set[tuple[int, int]]
    ) -> bool:
        next_visited = visited | {pos}
        if self.path_neighbor_count(pos, visited) > 2:
            return True
        for direction in Direction:
            neighbor = self.neighbor_pos(pos, direction)
            if (
                neighbor in visited
                and self.path_neighbor_count(neighbor, next_visited) > 2
            ):
                return True
        return False

    def can_step_to(
        self,
        pos: tuple[int, int],
        visited: set[tuple[int, int]]
    ) -> bool:
        if not self.is_in_bounds(pos):
            return False
        if pos in self.blocked or pos in visited:
            return False
        if pos in self.branch_cells:
            return False
        if self.path and pos in self.pathcells:
            return False
        if self.would_clump(pos, visited):
            return False
        return True

    def valid_directions(
        self,
        pos: tuple[int, int],
        visited: set[tuple[int, int]]
    ) -> list[Direction]:
        valid_directions = []
        for direction in Direction:
            if self.can_step_to(self.neighbor_pos(pos, direction), visited):
                valid_directions.append(direction)
        return valid_directions

    def distance(
        self,
        pos: tuple[int, int],
        exit: tuple[int, int]
    ) -> int:
        return abs(pos[0] - exit[0]) + abs(pos[1] - exit[1])

    def weighted_choice(
        self,
        options: list[tuple[Direction, int]]
    ) -> Direction:
        total = sum(weight for _, weight in options)
        pick = random.randint(1, total)
        current = 0
        for item, weight in options:
            current += weight
            if pick <= current:
                return item
        raise RuntimeError("Weighted choice failed to select an option")

    def create_path(self) -> bool:
        entry = self.entry
        exit = self.exit
        path: list[Direction] = []
        visited = set()

        def walk(pos: tuple[int, int]) -> bool:
            self.steps += 1
            if self.steps > self.max_steps:
                return False
            if pos in visited:
                return False
            visited.add(pos)
            if pos == exit:
                return True

            directions = self.valid_directions(pos, visited)
            direction_weights = []
            for direction in directions:
                possible_move = self.neighbor_pos(pos, direction)
                old_distance = self.distance(pos, exit)
                new_distance = self.distance(possible_move, exit)
                if new_distance < old_distance:
                    weight = 5  # closer to exit
                elif new_distance == old_distance:
                    weight = 3  # sideways
                else:
                    weight = 1  # temporary detour
                direction_weights.append((direction, weight))
            while direction_weights:
                direction = self.weighted_choice(direction_weights)
                direction_weights = [
                    (d, w) for d, w in direction_weights if d != direction
                ]
                next_pos = self.neighbor_pos(pos, direction)
                self.open_wall(pos, direction)
                if walk(next_pos):
                    path.insert(0, direction)
                    return True
                self.close_wall(pos, direction)
            visited.discard(pos)
            return False

        for attempt in range(5):
            self.steps = 0
            path = []
            visited = set()
            if walk(entry):
                self.path = path
                self.init_pathcells()
                return True
        raise RuntimeError("Could not create a valid path from entry to exit")

    def get_solution_cells(self) -> set[tuple[int, int]]:
        solution_cells: set[tuple[int, int]] = set()
        pos = self.entry
        for direction in self.path:
            solution_cells.add(pos)
            pos = self.neighbor_pos(pos, direction)
        solution_cells.add(pos)
        return solution_cells

    def grow_dead_end(self, start: tuple[int, int]) -> None:
        pos = start
        branch_cells = {start}
        frontier = [start]
        while frontier:
            pos = random.choice(frontier)
            directions = self.valid_directions(pos, branch_cells)
            if not directions:
                frontier.remove(pos)
                continue
            direction = random.choice(directions)
            self.open_wall(pos, direction)
            next_pos = self.neighbor_pos(pos, direction)
            branch_cells.add(next_pos)
            frontier.append(next_pos)
        self.branch_cells.update(branch_cells)

    def can_fill_to(
        self,
        pos: tuple[int, int],
        opened: set[tuple[int, int]]
    ) -> bool:
        if not self.is_in_bounds(pos):
            return False
        if pos in self.blocked or pos in opened:
            return False
        return True

    def find_expandable_cells(self) -> list[tuple[int, int]]:
        opened_cells = self.branch_cells | self.pathcells
        expandable = []
        for cell in opened_cells:
            for direction in Direction:
                neighbor = self.neighbor_pos(cell, direction)
                if self.can_fill_to(neighbor, opened_cells):
                    expandable.append(cell)
                    break
        return expandable

    def create_dead_ends(self) -> None:
        solution_cells = list(self.pathcells)
        random.shuffle(solution_cells)
        for pick in solution_cells:
            self.grow_dead_end(pick)
        selection = self.find_expandable_cells()
        while selection:
            pick = random.choice(selection)
            self.grow_dead_end(pick)
            selection = self.find_expandable_cells()

    def would_make_2x2(
        self,
        pos: tuple[int, int],
        direction: Direction
    ) -> bool:
        neighbor = self.neighbor_pos(pos, direction)
        if not self.is_in_bounds(neighbor):
            return False
        for orthogonal in Direction:
            if orthogonal == direction or orthogonal == OPPOSITE[direction]:
                continue
            orth_neighbor = self.neighbor_pos(pos, orthogonal)
            orth_neighbor_2 = self.neighbor_pos(neighbor, orthogonal)
            if not self.is_in_bounds(orth_neighbor):
                continue
            if not self.is_in_bounds(orth_neighbor_2):
                continue
            if (
                not self.is_wall_closed(pos, orthogonal) and
                not self.is_wall_closed(neighbor, orthogonal) and
                not self.is_wall_closed(orth_neighbor, direction)
            ):
                return True
        return False

    def proliferate_dead_ends(self) -> None:
        cells = list(self.branch_cells | self.pathcells)
        for cell in cells:
            for direction in Direction:
                neighbor = self.neighbor_pos(cell, direction)
                if neighbor in cells:
                    if (
                        self.is_wall_closed(cell, direction)
                        and not self.would_make_2x2(cell, direction)
                    ):
                        if (random.random() < 0.2):
                            self.open_wall(cell, direction)

    def generate(self) -> None:
        if self.seed is not None:
            random.seed(self.seed)
        else:
            random.seed(time.time_ns())
        self.blocked.clear()
        self.branch_cells.clear()
        self.path.clear()
        self.pathcells.clear()
        self.steps = 0
        for x in range(self.width):
            for y in range(self.height):
                self.maze[x][y] = 0b1111  # All walls closed\
        self.draw_42()
        self.create_path()
        self.create_dead_ends()
        if not self.perfect:
            self.proliferate_dead_ends()

    def write_maze(self, output: str) -> None:
        entry = self.entry
        exit = self.exit
        path = self.path
        out = []
        for y in range(self.height):
            out.append("".join(f"{self.maze[x][y]:X}"
                               for x in range(self.width)))

        with open(output, "w") as f:
            for line in out:
                print(line, file=f)
            print("", file=f)
            print(f"{entry[0]},{entry[1]}", file=f)
            print(f"{exit[0]},{exit[1]}", file=f)
            if path is not None:
                print("".join(direction.name for direction in path), file=f)


class MazeGenerator(Maze):
    pass
