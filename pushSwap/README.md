*This project has been created as part of the 42 curriculum by leonmarq and rokuni*

# Description
it's about sorting numbers with two the stacks a and b. all values get loaded to a first and after sorting have to be sorted from lowest to highest in a.

these numbers all have to be unique and are handed in as the ./push_swap programs arguments.
The numbers are sorted using two stacks, stack A & B. stack A is filled up first and B remains empty. commands available are: `pa`,`pb`,`sa`,`sb`,`ss`,`ra`,`rb`,`rr`,`rra`,`rrb`,`rrr`

As required by the subject, the program only outputs the commands used to sort the numbers, not the actual result.

## Optional arguments
- Strategy can be defined to set one of 4 Strategies
	1. Simple: O(n^2)
	2. Medium: O(n*sqrt(n))
	3. Complex: O(n*log(n))
	4. Adaptive: best Algorithm based on initial disorder
- Benchmark mode outputs a summary of
  - initial disorder
  - strategy used
  - total sorting operation count
  - seperate sorting operation counts
- Debug mode prints both stacks while the program runs at specific points

## Output
- fd 1: the operations used while sorting
- fd 2: benchmark output if bench is activated

# Instructions

## Basic program
1. run `make`
2. execute `./push_swap` with an arbitrary amount of unique integer values
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG`

## Testing
### institutional
1. download the checker fitting your OS from sources.
2. append the checker to command via pipe
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG | ./checker_linux $ARG`

### bonus part
1. run `make checker`
2. use it like the provided checker
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG | ./checker $ARG`

```
$>./checker 3 2 1 0
sa
rra
pb
KO
```
> this edge case with no input can not be checked with allowed setup. it will wait for input

### visual
1. `git clone https://gitlab.com/lmarquar/push_swap_visualizer`
2. `./push_swap_visualizer/visips`


### debugging
all tests from subject
- `valgrind --leak-check=full ./push_swap --simple 5 4 3 2 1`
- `shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)`
- `ARG="4 67 3 87 23"; ./push_swap --bench --adaptive $ARG 2> bench.txt | ./checker_linux $ARG`
- `valgrind --leak-check=full ./push_swap --adaptive 0 one 2 3`
bonus:
- KO: `ARG=($(shuf -i 0-2147483647 -n 100)); echo "pb"| valgrind --leak-check=full ./checker $ARG`
- `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG | valgrind --leak-check=full ./checker $ARG`
  - still reachable memory from gnl, not a problem

## Setting Flags
set them directly after the executable, before the integers
- Benchmark: `--bench`
- Debug: `--debug`
- Strategies: one of `--simple`,`--medium`,`--complex`,`--adaptive`
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap --bench --adaptive $ARG`


# Algorithms used
- we work with a linked list to sort, which can store 2  numbers. find it in the header file.

## Simple
Insertions Sort
1. find lowest number in Stack
2. push lowest element to B
3. iterate through A pushing always the next lowest value
4. push back everything to A

## Medium
Chunk based
1. presorts the list by assigning indexes to each element
2. overwrites original values with indexes to make space
3. creates `sqrt(n)` chunks and assigns them evenly to the indexes in ascending order.
4. push everything to B starting with the lowest chunk, while deciding wether to reverse rotate a based on "lowest cost" for next element based on chunk
5. find the biggest value of B and push to A
6. chunk by chunk, find the next biggest value checking the top value of A and push back, while decing how to rotate B again based on "lowest cost" for next element based on value

## Complex
Quicksort variation
- we have the following loop, roughly it finds pivots/medians, and creates partitions with help of splitting between lower and heigher halfes. Placing the pivot smartly spares steps. Then a *sort3* hardcoded algorithm if a partition is smaller or equal to 3 elements.
  - divides in halves
  - uses partitions
  - takes advantage of pivot being highest new number of current partition, by placing it on top

# Resources
- Algorithms Illuminated: https://timroughgarden.org
- ChatGPT and copilot for thinking support
- https://www.reddit.com/r/cpp_questions/comments/oqpa3f/sqrt_function_that_11_faster_is_it_a_good/
- https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a
