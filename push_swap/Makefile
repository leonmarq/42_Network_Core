CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
NAME	:= push_swap
VISUALIZER	:= push_swap_visualizer/push_swap-visualizer

PRINTFD_DIR		:= ft_dprintf
LIBFTPRINTFD	:= $(PRINTFD_DIR)/libftprintfd.a

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

$(NAME): $(LIBFTPRINTFD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTPRINTFD) -o $(NAME)
	$(MAKE) clean

$(LIBFTPRINTFD):
	$(MAKE) -C $(PRINTFD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) *.o
	$(MAKE) -C $(PRINTFD_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

visualizer: $(NAME)
	./$(VISUALIZER)

revisualizer: re
	./$(VISUALIZER)

.PHONY: all clean fclean re visualizer revisualizer
