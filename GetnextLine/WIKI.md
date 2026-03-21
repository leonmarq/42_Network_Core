# get_next_line (bonus) — How the logic works

This document explains the flow of your `get_next_line_bonus.c` step by step, with the goal of understanding **why it works** and **how each function collaborates**.

---

## 1) Big picture

`get_next_line(fd)` must return:
- the next line from `fd` (including `\n` when present), or
- `NULL` when there is nothing left or on error.

In bonus mode, you can call it on **multiple file descriptors** interleaved, so each `fd` needs its own leftover buffer.

Your implementation does this with:

- `static char *buffer[1024];`
  One persistent buffer slot per `fd`.
- A dynamic `t_line` object (`line.s`, `line.len`, `line.cap`)
  Used to build the output line progressively.

---

## 2) Core data model

You have two memory zones at runtime:

1. **Per-FD persistent stash (`buffer[fd]`)**
   - Stores unread characters from previous calls.
   - Survives between calls because it is `static`.

2. **Per-call dynamic output line (`line.s`)**
   - Starts empty every call.
   - Grows when needed.
   - Returned to caller when a line is ready.

---

## 3) Function-by-function logic

## `grow_line(t_line *line, size_t add)`

Purpose:
- Ensure `line->s` has enough capacity for:
  - current content (`line->len`)
  - incoming chunk (`add`)
  - null terminator (`+1`)

How:
- Starts from `line->cap`.
- Doubles (`nc *= 2`) until it fits.
- Allocates new memory, copies old chars manually, frees old memory.
- Updates `line->s` and `line->cap`.

Return:
- `0` success
- `-1` allocation failure

---

## `append(t_line *line, char *buffer)`

Purpose:
- Move one logical chunk from `buffer` into `line`.
- Chunk = up to newline (`\n`) inclusive, or whole buffer content if no newline.

Steps:
1. Compute `use`:
   - Scan until `\n` or `\0`.
   - Include `\n` if found.
2. Ensure `line` capacity with `grow_line`.
3. Copy first `use` chars from `buffer` to end of `line->s`.
4. Shift remaining `buffer` chars to the front (leftover stash).
5. Decide status:
   - return `1` if appended chunk ended with `\n` (line complete)
   - return `2` if no newline yet (need more reads)
   - return `-1` on memory error

This function is the key “consume from stash, keep the rest” behavior.

---

## `createline(int fd, char *buffer, t_line *line)`

Purpose:
- Build one full output line in `line`, using:
  - existing stash in `buffer`
  - fresh reads from `fd` when stash is empty

Loop:
- While line not complete (`flag > 1`):
  - If `buffer` empty → read `BUFFER_SIZE` bytes into it.
  - If read error (`<0`) → return `-1`.
  - If EOF (`flag == 0`) and no data accumulated (`line->len == 0`) → return `-2` (true end).
  - Otherwise append from buffer (`append`).

Return values:
- `1` line completed by newline
- `2` continue state (internal loop value)
- `0` EOF reached after collecting chars without trailing newline
- `-1` read/malloc error
- `-2` EOF with no line at all

---

## `get_next_line(int fd)`

Top-level orchestration:

1. Validate `fd` and `BUFFER_SIZE`.
2. Validate descriptor with `read(fd, 0, 0)`.
   - If invalid: free `buffer[fd]`, return `NULL`.
3. Init local line:
   - `cap = 32`, `len = 0`, allocate `line.s`.
4. Allocate `buffer[fd]` if first time.
5. Call `createline(fd, buffer[fd], &line)`.
6. Decide what to return:
   - Return `line.s` when a line exists:
     - newline line (`flag > 0`) OR
     - last line at EOF without newline (`flag == 0 && line.len > 0`)
   - Else free everything and return `NULL`.

Important detail:
- On final EOF after returning last partial line, you should free `buffer[fd]`.

---

## 4) Why static buffer array is needed in bonus

Without bonus, one static stash is enough.
With bonus, calls can interleave:

- `get_next_line(fd1)`
- `get_next_line(fd2)`
- `get_next_line(fd1)`

So each fd needs independent leftover state; hence `buffer[fd]`.

---

## 5) Typical execution example

Assume `BUFFER_SIZE = 4`, file contains `abc\ndef`.

Call 1:
- read `abc\n`
- append includes newline
- return `"abc\n"`
- stash now empty

Call 2:
- read `def` then EOF
- append `def` (no newline)
- at EOF return `"def"` (last line without `\n`)

Call 3:
- EOF and nothing accumulated
- return `NULL`

---

## 6) Common pitfalls (and what your code addresses)

- **Dropping last line without newline**
  Must return it once before returning `NULL`.
- **Leaking per-fd stash**
  Free `buffer[fd]` when done (EOF finalization or invalid fd).
- **Using one static buffer for all fds**
  Breaks bonus interleaving; array is required.
- **Forgetting null terminators after copies/shifts**
  Causes undefined behavior in string ops.

---

## 7) Mental model to keep

Think of the algorithm as two phases per call:

1. **Accumulate** into `line.s` from stash/read until newline or EOF.
2. **Finalize**:
   - if you got chars: return them
   - if none: return `NULL`

That is the entire design of a robust `get_next_line`.

---

If you want, the next step is a second wiki page with an **annotated line-by-line walkthrough** of your exact source (with comments on each block).
