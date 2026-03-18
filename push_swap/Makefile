CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
LFLAGS	:= -crs
NAME	:= push_swap
PUAR	:= push_swap.a
PUDIR	:= src/
PSRC	:= push_swap.c push_swap_utils.c push_swap_commands.c \
			 push_swap_commands2.c push_swap_commands3.c \
			 push_swap_sort.c find_median.c small_funcs.c sort3.c \
			 a_to_b.c b_to_a.c
POBJ	:= $(PSRC:.c=.o)
LBDIR	:= libft/
LBAR	:= libft/libft.a
LOBJ	:= ft_memset.o ft_memcpy.o ft_memccpy.o ft_bzero.o \
			 ft_atoi.o ft_memmove.o ft_memchr.o ft_memcmp.o \
			 ft_strlen.o ft_strlcpy.o ft_strlcat.o ft_strchr.o \
			 ft_strrchr.o ft_strnstr.o ft_strncmp.o ft_isalpha.o \
			 ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
			 ft_toupper.o ft_tolower.o ft_calloc.o ft_strdup.o ft_substr.o \
			 ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o \
			 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
MAIN	:= main.c

all: $(LBAR) $(NAME) 

re: fclean all

$(NAME): $(PUAR)
	$(CC) $(CFLAGS) $(MAIN) $(PUAR) -o $@

$(PUAR): $(LOBJ) $(POBJ)
	ar $(LFLAGS) $@ $(POBJ) $(LOBJ)

$(POBJ):
	cd $(PUDIR) && $(CC) $(CFLAGS) -c $(PSRC)
	cd $(PUDIR) && mv $(POBJ) ..

$(LOBJ):
	ar -x $(LBAR)

$(LBAR):
	cd $(LBDIR) && make

clean:
	rm -f $(POBJ) $(LOBJ)
	rm -f $(PUAR)
	cd $(LBDIR) && make fclean
	rm -f __.SYMDEF\ SORTED

fclean:
	rm -f $(POBJ) $(LOBJ)
	rm -f $(PUAR)
	rm -f $(NAME)
	cd $(PUDIR) && rm -f $(POBJ)
	cd $(LBDIR) && make fclean
	rm -f a.out

.PHONY: all re clean fclean
