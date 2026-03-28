CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
LDFLAGS		:= -no-pie -Lft_dprintf
LDLIBS		:= -lftprintfd
NAME		:= push_swap
NAME_C		:= checker

PRINTFD_DIR		:= ft_dprintf
GNL_DIR			:= get_next_line
LIBFTPRINTFD	:= $(PRINTFD_DIR)/libftprintfd.a

SRC_DIR		:= src
AUX_DIR		:= src/aux
ALGS_DIR	:= src/algs
OPS_DIR		:= src/ops
S3_DIR		:= src/s3
QS_DIR		:= src/algs/qsort
CS_DIR		:= src/algs/csort
CHECKER_DIR	:= src/ckr
PS_MAIN		:= $(SRC_DIR)/main.c
CKR_MAIN	:= $(CHECKER_DIR)/main_checker.c
SRCS	:= $(AUX_DIR)/push_swap_utils.c \
		$(AUX_DIR)/utils.c \
		$(AUX_DIR)/parsing_utils.c \
		$(AUX_DIR)/getters.c \
		$(AUX_DIR)/getters2.c \
		$(AUX_DIR)/getters_p.c \
		$(AUX_DIR)/debug_utils.c \
		$(AUX_DIR)/list_utils.c \
		$(AUX_DIR)/small_funcs.c \
		$(AUX_DIR)/entry_utils.c \
		$(AUX_DIR)/math.c \
		$(OPS_DIR)/push_swap_commands.c \
		$(OPS_DIR)/push_swap_commands2.c \
		$(OPS_DIR)/push_swap_commands3.c \
		$(ALGS_DIR)/algorithm_simple.c \
		$(ALGS_DIR)/algorithm_medium.c \
		$(ALGS_DIR)/algorithm_complex.c \
		$(S3_DIR)/sort3.c \
		$(S3_DIR)/sort3_b_pa.c \
		$(S3_DIR)/sort3_b_pa_rev.c \
		$(QS_DIR)/a_to_b.c \
		$(QS_DIR)/b_to_a.c \
		$(QS_DIR)/b_to_a_rev.c \
		$(QS_DIR)/find_median.c \
		$(CS_DIR)/chunk_sort.c \
		$(CS_DIR)/utils.c \
		$(SRC_DIR)/algorithm_picker.c \
		$(SRC_DIR)/benchmark.c \
		$(SRC_DIR)/run_ps.c

SRCS_C	:= $(CHECKER_DIR)/checker.c \
			$(GNL_DIR)/get_next_line.c \
			$(GNL_DIR)/get_next_line_utils.c \
			$(CHECKER_DIR)/checker_commands.c \
			$(CHECKER_DIR)/checker_commands2.c \
			$(CHECKER_DIR)/checker_commands3.c

OBJS	:= $(SRCS:.c=.o)
OBJS_C	:= $(SRCS_C:.c=.o)
OBJ_PM := $(PS_MAIN:.c=.o)
OBJ_CM := $(CKR_MAIN:.c=.o)

all: $(NAME)

$(NAME_C): $(LIBFTPRINTFD) $(OBJ_CM) $(OBJS_C) $(OBJS)
	$(CC) $(CFLAGS) $(OBJ_CM) $(OBJS_C) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME_C)

$(NAME): $(LIBFTPRINTFD) $(OBJ_PM) $(OBJS)
	$(CC) $(CFLAGS) $(OBJ_PM) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFTPRINTFD):
	$(MAKE) -C $(PRINTFD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_C) $(OBJ_PM) $(OBJ_CM)
	$(MAKE) -C $(PRINTFD_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_C)

	$(MAKE) -C $(PRINTFD_DIR) fclean

re: fclean all

.PHONY: all clean fclean re visualizer revisualizer
