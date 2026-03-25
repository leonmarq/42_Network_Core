*This project has been created as part of the 42 curriculum by leonmarq*

# Description
it's about sorting numbers with two the stacks a and b. all values get loaded to a first and after sorting have to be sorted from lowest to highest in a.


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

## Output
- fd 1: the operations used while sorting
- fd 2: benchmark output if bench is activated

# Instructions
run `make`

## Basic program
execute `./push_swap` with an arbitrary amount of unique integer values
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG`

## Testing
1. download the checker fitting your OS from sources.
2. append the checker to command via pipe
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap $ARG | ./checker_linux $ARG`

## Setting Flags
set them directly after the executable, before the integers
- Benchmark: `--bench`
- Strategies: one of `--simple`,`--medium`,`--complex`,`--adaptive`
> Example: `ARG=($(shuf -i 0-2147483647 -n 100)); ./push_swap --bench --adaptive $ARG`

# Resources
- Algorithms Illuminated: https://timroughgarden.org
- ChatGPT and copilot for thinking support

# Algorithms used
- we work with a linked list to sort, find it in the header file.

## Medium
Chunk based
1. presorts the list

## Complex
Quicksort variation
- we have the following loop, roughly it finds pivots/medians, and creates partitions with help of splitting between lower and heigher halfes. Placing the pivot smartly spares steps. Then a *sort3* hardcoded algorithm if a partition is smaller or equal to 3 elements.
- the following desciption is more detailed, but hard to read:
1. find pivot/median in A, push lower value to b, assign Partition 1 and place the pivot on top of B
2. 1. repeat and name partitions in increasing value until we are left with 1-2 values in A.
3. 1. take the top(smallest partition in B), push top value to A, remove partitioning
4. 2. find pivot in B and move bigger values to A, value partition to (biggest partition in A) + 1, place pivot on top of A
5. again in A, if sorted, partitions to 0.
6. 1. Else, start at heighest partition(bottom or top), find pivot and move lower to b.
7. 2. New B partition: heighest in B + 1.
8. in B, start at heighest partition(bottom or top), find pivot and move lower to b


these numbers alll have to be unique and are handed in as the ./push_swap programs arguments.
The numbers are sorted using two stacks, stack A & B. stack A is filled up first and B remains empty.
We are allowed to rearrange the stacks with a few different commands. For example "sa" swaps the top
two elements in stack a, "sb" does the same with b. There is more, but it would take too long to explain.

As required by the subject, the program only outputs the commands used to sort the numbers, not the actual result.
If you want the result, comment out the printlists(a, b) function in main.c, which prints the a and b stack ♫
