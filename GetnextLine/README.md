*This project has been created as part of the 42 curriculum by leonmarq*

# Description
- a function that returns a line read from a file descriptor as a `(char *)`
- Bonus part adds support for multiple file descriptors to be used at once

# Instructions
## Mandatory
1. include the function header
`#include "get_next_line.h"`
2. use `get_next_line(int fd)` in your C code
3. compile with `get_next_line.c get_next_line_utils.c` added
+ Example: `cc -Wall -Werror -Wextra main.c get_next_line.c get_next_line_utils.c`

## Bonus

1. place this as source `#include "get_next_line_bonus.h"`
2. use `get_next_line(int fd)` in your C code
3. compile with `get_next_line_bonus.c get_next_line_utils_bonus.c` added
+ Example: `cc -Wall -Werror -Wextra main.c get_next_line_bonus.c get_next_line_utils_bonus.c`

# Resources
1. standard library documentations and man pages
2. the subject
3. "Github Copilot" was used for fixing memory issues

# Algorithm
`get_next_line(fd)` works in 3 phases:

1. **Keep a persistent buffer (stash)**
   - Mandatory: one static buffer
   - Bonus: one static buffer per file descriptor (`buffer[MAX_FD]`)
   - The stash keeps leftover characters after returning a line.

2. **Build the next line dynamically**
   - Start with an empty dynamic line (`len`, `cap`, `char *s`).
     - length `len`
     - allocated space `cap`
     - the already saved characters `char *s`
   - If the stash is empty, call `read(fd, stash, BUFFER_SIZE)`.
   - Copy from stash into the line until `\n` (included) or end of stash.
   - Shift remaining stash content to the front for the next call.
   - Grow line capacity when needed.

3. **Return based on the final state**
   - If a newline is reached: return the built line.
   - If EOF is reached and the line has data: return the last line (without `\n`).
   - If EOF is reached and no data could be read: return `NULL`.
   - On error (read/allocation): free and return `NULL`.
