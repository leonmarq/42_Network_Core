*This project has been created as part of the 42 curriculum by leonmarq*

# Description
Codexion is a more complex variation of the philosophers problem invented 1965 by Edsger Dijkstra from the Netherlands.
It teaches the basics of multithreading in C.

Instead of Philosophers and forks, here we have coders and dongles. Furthermore the they also have different actions, which are:
1. compile (dongles needed)
2. debug
3. refactor
all three of them have a defined time to execute it, indifferent from the philososphers, where only 2 actions are defined in timeframe.

## Blocking cases handled
### deadlock prevention
In the case of waiting for dongles, cond is used to wait for a broadcast. I emit it once a dongle is free to use, or if the program is supposed to stop. Furthermore a coder only takes a dongle, if it can take both.

### burnout detection
by looping inside a monitor-thread in short pulses, i can realize a coder is dead, display the message and tell the other coders to stop.

### log serialization
there is one mutex just for printing and only one function which accesses it which builds the message based on time, coder and a variable from the action enum.

## Thread synchronization mechanism
we use the pthread library `<pthread.h>` and its functions to create one thread for each coder and manage resources with it's common tools.

### use of mutex
3 are in use.
1. dongle mutex: antideadlock of dongles
2. print mutex: for secure output
3. dead mutex: setting and reading dead booleans

#### dongle mutex elaborated
when locked, the pthread_cond statement gets called in a loop to wait until the resource we want (2 dongles) is actually avaiable to the coder and cooled down.
the cond gets wakedup if:
1. the monitor-thread contributes by broadcasting once a dongle cooled down a short time ago.
2. another coder just finished and frees the dongles.

once in use the mutex is unlocked, then the coder compiles, and after compile we need to lock it again just to release the dongles again.

### case of burnout
in case of burnout, we always release both dongles if in use and then unlock any locked mutexes and return. then it gets detected by the monitor thread, which displays the correalating message and quits the program.

# Instructions
## How to execute
`./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler]`

## tests
for quick examples execute `./test/codexecutor.sh`

# Resources
- https://en.wikipedia.org/wiki/Dining_philosophers_problem

## use of AI
- openai was my go to for explaining me how to use mutexes and cond efficiently.
