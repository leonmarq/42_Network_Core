import unittest
import mazegen
import subprocess


class TestWrongInput(unittest.TestCase):
    def test_wrong_input(self) -> None:
        with self.assertRaises(ValueError):
            mazegen.Maze(10, 10, (1, 1), (11, 11), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(21, 30, (9, 15), (19, 29), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(10, 10, (1, 1), (10, 10), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(-10, 10, (1, 1), (9, 9), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(10, -10, (1, 1), (9, 9), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(5, 5, (1, 1), (4, 4), True)
        with self.assertRaises(ValueError):
            mazegen.Maze(6, 6, (1, 1), (5, 5), True)

    def test_overlapping_start_end(self) -> None:
        with self.assertRaises(ValueError):
            mazegen.Maze(10, 10, (1, 1), (1, 1), True)


class TestOutput(unittest.TestCase):
    def test_my_command(self) -> None:
        file = "tests/configs/test_output.txt"
        maze = mazegen.Maze(10, 10, (1, 1), (9, 9), True)
        maze.generate()
        maze.write_maze(file)
        with self.subTest("Output should be valid"):
            result = subprocess.run(
                ["python3", "tests/output_validator.py", file],
                capture_output=True,
                text=True,
            )
        assert result.returncode == 0


class TestFileParsing(unittest.TestCase):
    def test_invalid_config_files(self) -> None:
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config("tests/configs/nonexistent_file.txt")
        self.assertEqual(
            str(context.exception),
            "Error: Config file 'tests/configs/nonexistent_file.txt' not found"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config(
                "tests/configs/invalid_type_tuple_long.txt")
        self.assertEqual(
            str(context.exception),
            "Error: ENTRY must be in x,y format"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config(
                "tests/configs/invalid_type_tuple_short.txt")
        self.assertEqual(
            str(context.exception),
            "Error: EXIT must be in x,y format"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config("tests/configs/invalid_type_for_bool.txt")
        self.assertEqual(
            str(context.exception),
            "Error: PERFECT must be 'True' or 'False'"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config(
                "tests/configs/invalid_type_for_width.txt")
        self.assertEqual(
            str(context.exception),
            "Error: WIDTH must be an integer"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config("tests/configs/invalid_format_middle.txt")
        self.assertEqual(
            str(context.exception),
            "Error: invalid configuration line format"
        )
        with self.assertRaises(ValueError) as context:
            mazegen.Maze.from_config("tests/configs/invalid_missing_key.txt")
        self.assertEqual(
            str(context.exception),
            "Error: missing required key WIDTH"
        )


class TestConsistency(unittest.TestCase):
    def test_consistency(self) -> None:
        maze1 = mazegen.Maze.from_config("tests/configs/valid_with_seed.txt")
        maze2 = mazegen.Maze.from_config("tests/configs/valid_with_seed.txt")
        self.assertEqual(maze1.maze.tolist(), maze2.maze.tolist())
        maze1.generate()
        self.assertEqual(maze1.maze.tolist(), maze2.maze.tolist())


if __name__ == '__main__':
    unittest.main()
