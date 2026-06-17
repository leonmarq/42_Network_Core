install:
	python3 -m venv .venv
	.venv/bin/python -m pip install -r requirements.txt

run:
	.venv/bin/python a_maze_ing.py config.txt

debug:
	.venv/bin/python -m pdb a_maze_ing.py config.txt

test:
	.venv/bin/python -m unittest tests/test_*.py

clean:
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type d -name ".pytest_cache" -exec rm -rf {} +
	find . -type d -name ".mypy_cache" -exec rm -rf {} +

fclean: clean
	rm -rfd .venv
	rm -f maze.txt
	rm -rfd dist
	rm -rf build
	rm -rfd mazegen.egg-info
	rm -rfd .venv-test

build:
	python3 -m build

lint:
	flake8 .
	mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	flake8 .
	mypy . --strict
