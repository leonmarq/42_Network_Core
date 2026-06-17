from setuptools import setup

setup(
    name="mazegen",
    version='1.0.0',
    packages=["mazegen"],
    install_requires=[
        'pydantic>=2',  # Define dependencies here
        'numpy>=1.20',  # Define dependencies here
    ],
    author='leonmarq',
    description=(
        'A simple pip-installable package' +
        'for maze generation and display'
    ),
)
