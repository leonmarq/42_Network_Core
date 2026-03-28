*This project has been created as part of the 42 curriculum by leonmarq*

> [!INFO]
> same like ft_printf but prints to fd: 2 instead of 1

- the function imitates the behaviour of printf with less features than the original
- it handles these conversions: `cspdiuxX%`
- Bonus: manages any combinations of following flags: `-0.`

# Instructions
1. create the library `libftprintf.a` with `make`
2. add the header `#include "ft_dprintf.h`
3. use the function `ft_dprintf(<content>)`
4. Link the library when compiling
- Example:

```
cc main.c libftprintf.a
```

## Cheatsheet for usable commands
- %c Prints a single character.
- %s Prints a string (as defined by the common C convention).
- %p The void * pointer argument has to be printed in hexadecimal format.
- %d Prints a decimal (base 10) number.
- %i Prints an integer in base 10.
- %u Prints an unsigned decimal (base 10) number.
- %x Prints a number in hexadecimal (base 16) lowercase format.
- %X Prints a number in hexadecimal (base 16) uppercase format.
- %% Prints a percent sign.

# Resources
1. standard library documentations and man pages
2. the subject
3. "Github Copilot" was used for fixing memory issues
4. "https://www.geeksforgeeks.org/" for in depth knowledge
5. "https://cplusplus.com/reference/cstdio/printf/"

# Algorithm
## Explanation
1. start a `va_list` based on input
2. parse everything from the `va_list` and `format` sorted into a big linked list `t_plist`
3. end the `va_list`
4. check list for faulty elemets and minor corrects special cases
5. account for precision and pad if needed
6. prints string elements one by one and accounts for `c` with `-` 0 case
7. frees list with content
8. returns the number of printed characters

## Justification
- i first parse everything to a list first and output at end of program.
  - This makes corrections and string manipulations easier in my opinion.

## List explained
- `char	*sraw`: current part of the first arguments string
- `char	*s`: final formatted string ready for output
- `char	type`: current conversion-type (if there is one0)
- `int	nbr`: stores integer values
bonus:
- `int	minus`: 1 if `-` in conversion-flag left justifies
- `int	nul`: 1 if `0` in conversion flag adds leftpadding of numbers
- `int	precision`: default `-1` handles `.<N>`
  - for strings: defines number of characters to be displayed
  - for numbers: defines minimum amount of digits and pads with 0's if needed

