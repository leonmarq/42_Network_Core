install:
	python3 -m venv .venv
	.venv/bin/python -m pip install -r requirements.txt

run:
	.venv/bin/python -m src.main

debug:
	.venv/bin/python -m debugpy --listen 5678 --wait-for-client src/main.py

test:
	.venv/bin/python -m unittest discover -s tests

clean:

lint:
	flake8 .
	mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	flake8 .
	mypy . --strict
