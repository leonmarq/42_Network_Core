# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 12:20:33 by leon              #+#    #+#              #
#    Updated: 2026/06/30 18:20:39 by leonmarq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
LIBS	:= -pthread
D_ADDR	:= -g -fsanitize=address
D_LEAK	:= -g -fsanitize=leak
D_THRD	:= -g -fsanitize=thread
SRC		:= init_data.c codexion.c core.c time.c time2.c misfit.c ft_calloc.c cleanup.c scheduler.c monitor.c check_args.c dongles.c
DIR		:= ./src
SRCS 	:= $(addprefix $(DIR)/, $(SRC))
NAME	:= codexion
NAME_A	:= codexion_address
NAME_V	:= codexion_valgrind
NAME_T	:= codexion_thread

all: $(NAME)

leaks: $(NAME_V)

addr: $(NAME_A)

thread: $(NAME_T)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(NAME_A): $(SRCS)
	$(CC) $(CFLAGS) $(D_ADDR) $(LIBS) $(SRCS) -o $(NAME)

$(NAME_V): $(SRCS)
	$(CC) $(CFLAGS) $(D_LEAK) $(LIBS) $(SRCS) -o $(NAME)

$(NAME_T): $(SRCS)
	$(CC) $(CFLAGS) $(D_THRD) $(LIBS) $(SRCS) -o $(NAME)


clean:

fclean:
	rm -f $(NAME) $(NAME_V) $(NAME_A) $(NAME_T)

re: fclean all

.PHONY: hel
