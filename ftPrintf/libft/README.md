*This project has been created as part of the 42 curriculum by leonmarq*
# Description
- a collection of small functions mostly imitating the behaviour of existing standard library functions

# Instructions
1. run make
2. include libft.h in your project and use the functions
3. append libft.a to your compile

# Resources
1. standard library documentations and man pages
2. the subject
3. "Github Copilot" was used for debugging, in particular ft_lstmap it helped out alot
4. "codex" helped out with creating a good README

# Details
## Part 1 - imitations of standart functions:
- ft_isalpha
- ft_isdigit
- ft_isalnum
- ft_isascii
- ft_isprint
- ft_strlen
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memmove
- ft_strlcpy
- ft_strlcat
- ft_toupper
- ft_tolower
- ft_strchr
- ft_strrchr
- ft_strncmp
- ft_memchr
- ft_memcmp
- ft_strnstr
- ft_atoi
- ft_calloc
- ft_strdup

## Part 2 - Additional functions (detailed descriptions)

### ft_substr
- Prototype: `char *ft_substr(char const *s, unsigned int start, size_t len);`
- Parameters:
  - `s`: The original string from which to create the substring.
  - `start`: The starting index of the substring within `s`.
  - `len`: The maximum length of the substring.
- Return value: The substring, or `NULL` if allocation fails.
- External function: `malloc`
- Description: Allocates memory and returns a substring from `s`. The substring starts at index `start` and has a maximum length of `len`.

### ft_strjoin
- Prototype: `char *ft_strjoin(char const *s1, char const *s2);`
- Parameters:
  - `s1`: The prefix string.
  - `s2`: The suffix string.
- Return value: The new string, or `NULL` if allocation fails.
- External function: `malloc`
- Description: Allocates memory and returns a new string, which is the result of concatenating `s1` and `s2`.

### ft_strtrim
- Prototype: `char *ft_strtrim(char const *s1, char const *set);`
- Parameters:
  - `s1`: The string to be trimmed.
  - `set`: The string containing the set of characters to be removed.
- Return value: The trimmed string, or `NULL` if allocation fails.
- External function: `malloc`
- Description: Allocates memory and returns a copy of `s1` with characters from `set` removed from the beginning and the end.

### ft_split
- Prototype: `char **ft_split(char const *s, char c);`
- Parameters:
  - `s`: The string to be split.
  - `c`: The delimiter character.
- Return value:
  - The array of new strings resulting from the split.
  - `NULL` if any allocation fails.
  - The returned structure must be released by freeing each string in the array, then freeing the array itself.
- External functions: `malloc`, `free`
- Description: Allocates memory and returns an array of strings obtained by splitting `s` using `c` as a delimiter. Each string is allocated independently, the array of pointers is also allocated dynamically, and the returned array is `NULL` terminated.

### ft_itoa
- Prototype: `char *ft_itoa(int n);`
- Parameters:
  - `n`: The integer to convert.
- Return value: The string representing the integer, or `NULL` if allocation fails.
- External function: `malloc`
- Description: Allocates memory and returns a string representing the integer received as an argument. Negative numbers must be handled.

### ft_strmapi
- Prototype: `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`
- Parameters:
  - `s`: The string to iterate over.
  - `f`: The function to apply to each character.
- Return value: The string created from successive applications of `f`, or `NULL` if allocation fails.
- External function: `malloc`
- Description: Applies `f` to each character of `s`, passing its index as the first argument and the character itself as the second. A new string is created to store the results.

### ft_striteri
- Prototype: `void ft_striteri(char *s, void (*f)(unsigned int, char*));`
- Parameters:
  - `s`: The string to iterate over.
  - `f`: The function to apply to each character.
- Return value: None.
- External function: None.
- Description: Applies `f` to each character of the string passed as argument, passing its index as the first argument. Each character is passed by address to `f` so it can be modified if necessary.

### ft_putchar_fd
- Prototype: `void ft_putchar_fd(char c, int fd);`
- Parameters:
  - `c`: The character to output.
  - `fd`: The file descriptor on which to write.
- Return value: None.
- External function: `write`
- Description: Outputs the character `c` to the specified file descriptor.

### ft_putstr_fd
- Prototype: `void ft_putstr_fd(char *s, int fd);`
- Parameters:
  - `s`: The string to output.
  - `fd`: The file descriptor on which to write.
- Return value: None.
- External function: `write`
- Description: Outputs the string `s` to the specified file descriptor.

### ft_putendl_fd
- Prototype: `void ft_putendl_fd(char *s, int fd);`
- Parameters:
  - `s`: The string to output.
  - `fd`: The file descriptor on which to write.
- Return value: None.
- External function: `write`
- Description: Outputs the string `s` to the specified file descriptor followed by a newline.

### ft_putnbr_fd
- Prototype: `void ft_putnbr_fd(int n, int fd);`
- Parameters:
  - `n`: The integer to output.
  - `fd`: The file descriptor on which to write.
- Return value: None.
- External function: `write`
- Description: Outputs the integer `n` to the specified file descriptor.

## Part 3 - Linked list functions (detailed descriptions)

### ft_lstnew
- Prototype: `t_list *ft_lstnew(void *content);`
- Parameters:
  - `content`: The content to store in the new node.
- Return value: A pointer to the new node.
- External function: `malloc`
- Description: Allocates memory and returns a new node. The `content` member is initialized with the given parameter, and `next` is initialized to `NULL`.

### ft_lstadd_front
- Prototype: `void ft_lstadd_front(t_list **lst, t_list *new);`
- Parameters:
  - `lst`: The address of a pointer to the first node of a list.
  - `new`: The address of a pointer to the node to be added.
- Return value: None.
- External function: None.
- Description: Adds the node `new` at the beginning of the list.

### ft_lstsize
- Prototype: `int ft_lstsize(t_list *lst);`
- Parameters:
  - `lst`: The beginning of the list.
- Return value: The length of the list.
- External function: None.
- Description: Counts the number of nodes in the list.

### ft_lstlast
- Prototype: `t_list *ft_lstlast(t_list *lst);`
- Parameters:
  - `lst`: The beginning of the list.
- Return value: Last node of the list.
- External function: None.
- Description: Returns the last node of the list.

### ft_lstadd_back
- Prototype: `void ft_lstadd_back(t_list **lst, t_list *new);`
- Parameters:
  - `lst`: The address of a pointer to the first node of a list.
  - `new`: The address of a pointer to the node to be added.
- Return value: None.
- External function: None.
- Description: Adds the node `new` at the end of the list.

### ft_lstdelone
- Prototype: `void ft_lstdelone(t_list *lst, void (*del)(void *));`
- Parameters:
  - `lst`: The node to free.
  - `del`: The address of the function used to delete the content.
- Return value: None.
- External function: `free`
- Description: Takes a node as parameter and frees its content using `del`. Frees the node itself but does not free the next node.

### ft_lstclear
- Prototype: `void ft_lstclear(t_list **lst, void (*del)(void *));`
- Parameters:
  - `lst`: The address of a pointer to a node.
  - `del`: The address of the function used to delete the content of the node.
- Return value: None.
- External function: `free`
- Description: Deletes and frees the given node and all its successors, using `del` and `free`. Finally sets the pointer to the list to `NULL`.

### ft_lstiter
- Prototype: `void ft_lstiter(t_list *lst, void (*f)(void *));`
- Parameters:
  - `lst`: The address of a pointer to a node.
  - `f`: The address of the function to apply to each node's content.
- Return value: None.
- External function: None.
- Description: Iterates through the list `lst` and applies `f` to the content of each node.

### ft_lstmap
- Prototype: `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));`
- Parameters:
  - `lst`: The address of a pointer to a node.
  - `f`: The address of the function applied to each node's content.
  - `del`: The address of the function used to delete a node's content if needed.
- Return value: The new list, or `NULL` if allocation fails.
- External functions: `malloc`, `free`
- Description: Iterates through `lst`, applies `f` to each node's content, and creates a new list resulting from successive applications of `f`. The `del` function is used to delete node content if needed.

## Further reference
