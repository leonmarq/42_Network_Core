import time
import sys
from mazegen import Maze
from visualizer import Display

if __name__ == "__main__":
    arguments = sys.argv[1:]
    tme = time.time_ns()
    file = ""

    if len(arguments) == 0:
        print("Usage: python a_maze_ing.py [config_file]")
        sys.exit(1)
    if arguments[0]:
        file = arguments[0]
    if not file:
        print("Error: No config file specified")
        print("Usage: python a_maze_ing.py [config_file]")
        sys.exit(1)
    try:
        open(file, "r").close()
    except FileNotFoundError:
        print(f"Error: Config file '{file}' not found")
        sys.exit(1)

    try:
        maze = Maze.from_config(file)
    except ValueError as e:
        print(e)
        sys.exit(1)
    display = Display(maze)
    display.render()
    maze.write_maze(maze.get_output_file())
    try:
        while True:
            print()
            print("== A-MAZE-ING ==")
            print("1. Regenerate a new maze")
            print("2. Show/Hide path from entry to exit")
            print("3. Rotate maze colors")
            print("4. Quit")
            answer = input("Choice: (1-4): ")
            if answer == "1":
                maze.generate()
                display.render()
                maze.write_maze(maze.get_output_file())
            elif answer == "2":
                display.toggle_path()
                display.render()
            elif answer == "3":
                display.rotate_colors()
                display.render()
            elif answer == "4":
                break
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"An error occurred: {e}")
