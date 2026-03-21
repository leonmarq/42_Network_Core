CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
NAME	:= push_swap

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRC_DIR	:= src
SRCS	:= main.c \
		$(SRC_DIR)/push_swap.c \
		$(SRC_DIR)/push_swap_utils.c \
		$(SRC_DIR)/push_swap_commands.c \
		$(SRC_DIR)/push_swap_commands2.c \
		$(SRC_DIR)/push_swap_commands3.c \
		$(SRC_DIR)/algorithm_simple.c \
		$(SRC_DIR)/algorithm_medium.c \
		$(SRC_DIR)/algorithm_complex.c \
		$(SRC_DIR)/find_median.c \
		$(SRC_DIR)/small_funcs.c \
		$(SRC_DIR)/sort3.c \
		$(SRC_DIR)/a_to_b.c \
		$(SRC_DIR)/b_to_a.c \
		$(SRC_DIR)/debug_utils.c \
		$(SRC_DIR)/benchmark.c
OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	$(MAKE) clean

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) *.o
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
