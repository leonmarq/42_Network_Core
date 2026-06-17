*This project has been created as part of the 42 curriculum by marimoha and leonmarq*

`a-maze-ing` is a Python maze generation project. The project generates a maze from a small configuration file, displays it in the terminal, and writes the generated maze to an output text file.

The reusable part of the project is packaged as `mazegen`, which exposes the `Maze` class and related direction/mapping constants. The command-line script `a_maze_ing.py` combines this generator with the terminal display layer from `visualizer`.

The generated maze is stored internally as a NumPy array. Each cell uses a 4-bit wall mask:

```text
bit 0: North wall
bit 1: East wall
bit 2: South wall
bit 3: West wall
```

A closed wall is represented by a `1` bit, and an open wall is represented by a `0` bit. The output file writes each cell as a hexadecimal value, followed by the entry coordinate, exit coordinate, and solution path.

## Instructions

### Install dependencies

The project depends on Python 3 and NumPy. For local development:

```sh
pip install -r requirements.txt
```

The `Makefile` also provides:

```sh
make install
```

### Run the project

Using the included sample config:

```sh
python3 a_maze_ing.py test_config.txt
```

or:

```sh
make run
```


During execution, the terminal menu supports:

```text
1. Regenerate a new maze
2. Show/Hide path from entry to exit
3. Rotate maze colors
4. Quit
```

### Build the package

The reusable generator package can be built as a wheel:

```sh
python3 -m build
```

This should create a file similar to:

```text
dist/mazegen-1.0.0-py3-none-any.whl
```

### Test the installed package

A clean way to test the wheel is to install it in a virtual environment and import it from outside the project directory:

```sh
python3 -m venv .venv-test
source .venv-test/bin/activate
python3 -m pip install --upgrade pip build
python3 -m build
python3 -m pip install dist/mazegen-1.0.0-py3-none-any.whl
python3 -c "from mazegen import Maze; print(Maze)"
```

## Config File Format

The config file uses one required `KEY=value` pair per line.

Complete structure:

```text
WIDTH=<integer>
HEIGHT=<integer>
ENTRY=<x>,<y>
EXIT=<x>,<y>
OUTPUT_FILE=<path>
PERFECT=<True|False>
```

Example:

```text
WIDTH=10
HEIGHT=10
ENTRY=1,1
EXIT=9,9
OUTPUT_FILE=maze.txt
PERFECT=True
```

Field meanings:

| Key | Meaning |
| --- | --- |
| `WIDTH` | Number of maze cells on the x-axis. |
| `HEIGHT` | Number of maze cells on the y-axis. |
| `ENTRY` | Entry coordinate as `x,y`. |
| `EXIT` | Exit coordinate as `x,y`. |
| `OUTPUT_FILE` | File where the generated maze is written. |
| `PERFECT` | Boolean config option parsed by the program. |

Coordinates are zero-indexed and must be inside the maze bounds.

## Output File Format

The generated output file has three parts:

1. The maze grid, where each character is a hexadecimal wall mask.
2. A blank line.
3. The entry coordinate, exit coordinate, and solution path.

Example:

```text
B951511553
C0387E853A
BAC0154542
C2FA87FFFA
D2FC4157FA
92FFFAFFFA
AC13FAFD52
83AAFAFFFA
AAA878153A
C44456C7C6

1,1
9,9
ESEEEENEESESSSSSSS
```

The final path line uses direction letters:

```text
N = north
E = east
S = south
W = west
```

## Maze Generation Algorithm

The current generator uses a randomized, but weighted, depth-first/backtracking approach to create a valid path from the entry to the exit.

The main path is created by recursively walking from the entry coordinate until the exit is reached. At each step, the algorithm:

1. Lists valid neighboring cells.
2. Rejects cells that are out of bounds, blocked, already visited, or likely to create unwanted clumps.
3. Gives higher weight to moves that reduce the Manhattan distance to the exit.
4. Chooses randomly among weighted directions.
5. Opens the wall between the current cell and the chosen neighbor.
6. Backtracks if the chosen route cannot reach the exit.

After the solution path exists, the generator grows dead-end branches from cells on the solution path and from expandable branch cells. It then optionally opens some extra connections while avoiding simple 2x2 open areas.

The project also draws a blocked `42` shape in the maze when the maze is large enough. If the maze is smaller than `7x7`, it rejects to generate.

## Why This Algorithm

This approach is a good fit for the project because it guarantees that the maze has at least one path from entry to exit before extra branches are added. The weighted direction choice makes the path more likely to progress toward the exit, while still allowing detours and randomness.

Compared with a completely random walk, the distance weighting reduces the chance of wasting too many steps. Compared with a fully deterministic algorithm, the random choices keep the output varied between runs and seeds.

The later dead-end growth step makes the maze feel less like a single corridor and more like an explorable maze, while the internal solution path remains available for display and output.

## Reusable Code

The reusable package is `mazegen`.

It exposes:

```python
from mazegen import Maze
from mazegen import Direction
```

Basic example:

```python
from mazegen import Maze

maze = Maze(
    width=10,
    height=10,
    entry=(1, 1),
    exit=(9, 9),
    perfect=True,
)

maze.generate()
array = maze.get_array()
path = maze.get_path()
maze.write_maze("maze.txt")
```

Reusable parts:

| Code | Purpose |
| --- | --- |
| `mazegen.Maze` | Main maze generation class. |
| `mazegen.Direction` | Direction enum for north, east, south, west. |
| `Maze.generate()` | Generates the maze. |
| `Maze.get_array()` | Returns the NumPy wall-mask array. |
| `Maze.get_path()` | Returns the solution path as directions. |
| `Maze.write_maze()` | Writes the generated maze to a file. |

The terminal display is separate in `visualizer.Display`. The current package configuration installs `mazegen`, while the CLI project uses both `mazegen` and `visualizer` locally.

## Features

- Config-driven maze generation.
- Terminal rendering with box-drawing characters.
- Colored entry, exit, walls, and path.
- Toggleable solution path display.
- Regeneration from the interactive menu.
- Maze color rotation.
- Optional random seed argument.
- Reusable `mazegen` package buildable as a wheel.
- Output file containing the maze, entry, exit, and solution path.
- Blocked `42` motif for mazes large enough to contain it.

## Technical Choices

- Python was used because it allows fast iteration and clean packaging.
- NumPy was used to represent the maze grid as a numeric array.
- A bit mask was used for walls because each cell only needs four wall states.
- `setuptools` was used to package the reusable generator as `mazegen`.
- The display logic was kept separate from maze generation so that the generator can be reused without terminal rendering.

## Team and Project Management

### Roles

Current draft for a solo project:

| Member | Role |
| --- | --- |
| leonmarq | Maze generation, config parsing, terminal display, packaging, testing, documentation. |
| marimoha | Support, Testing |

### Planning

Initial anticipated planning:

1. Understand the subject requirements and expected input/output format.
2. Design a config format.
3. Write the output file.
4. Generate a valid path from entry to exit.
5. Implement a basic maze representation to terminal.
6. Add branches/dead ends to make the maze more interesting.
7. Render the maze in the terminal.
8. Package the reusable generator as `mazegen`.
9.  Test imports, output files, and edge cases.
10. Complete the README.

How the planning evolved:

- The generator became more than a simple random walk because it needed reliable entry-to-exit paths.
- The display layer became its own module so the generation code stayed reusable.
- Packaging was added so the `Maze` class could be installed and imported with `pip`.
- The config and output format became important documentation topics because they define how the evaluator or another user interacts with the project.

### What Worked Well

- Separating `mazegen` from `visualizer` makes the core maze logic easier to reuse.
- The bit-mask representation keeps wall operations compact.
- The weighted path generation balances randomness with progress toward the exit.
- The interactive display makes it easier to visually inspect generated mazes.

### What Could Be Improved

- The `PERFECT` option should be verified and documented according to its final implemented behavior.
- More automated tests could check config parsing, maze bounds, output format, and path validity.
- The CLI argument parsing could be made more robust for missing arguments.
- The README should be updated when package behavior or advanced features change.
- a normal depth-first algorithm would massivly reduce code and complexity, while increasing randomness too.

### Tools Used

- Python 3
- NumPy
- setuptools
- Make
- pip / virtual environments
- Terminal-based testing
- AI assistance for README planning, packaging guidance, and documentation review

## AI Usage

Copilot and Codex where used as a tutoring and documentation assistant, not as a replacement for understanding the project.

Tasks where AI helped:

- Reviewing what sections the README needs according to the subject.
- Suggesting a README structure.
- Explaining how to document the config file format.
- Explaining how the `mazegen` package can be built and tested as a wheel.
- Identifying project details that should be documented, such as reusable code, output format, and algorithm choice.

Parts of the project affected by AI assistance:

- Documentation planning.
- Packaging explanation.
- README draft wording.

## Resources

Classic references useful for this project:

- Python Packaging User Guide: https://packaging.python.org/
- setuptools documentation: https://setuptools.pypa.io/
- Python `venv` documentation: https://docs.python.org/3/library/venv.html
- Python `enum` documentation: https://docs.python.org/3/library/enum.html
- NumPy documentation: https://numpy.org/doc/
- Maze generation algorithms overview: https://en.wikipedia.org/wiki/Maze_generation_algorithm
- Recursive backtracking maze generation: https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search
- Manhattan distance: https://en.wikipedia.org/wiki/Taxicab_geometry

