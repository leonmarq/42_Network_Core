# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 13:40:33 by lmarquar          #+#    #+#              #
#    Updated: 2026/03/23 12:19:36 by leonmarq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra
LFLAGS	:= -crs
NAME	:= libftprintfd.a
SUBDIR	:= libft/
SUBAR	:= libft/libft.a
PSRC	:= ft_dprintf.c ft_createstr.c ft_fillist.c \
			 ft_utils.c ft_completelist.c ft_hex.c
POBJ	:= $(PSRC:.c=.o)

all: $(SUBAR) $(NAME)

bonus: all


re: fclean all

$(NAME): $(SUBAR) $(POBJ)
	cp $(SUBAR) $(NAME)
	ar $(LFLAGS) $@ $(POBJ)

$(SUBAR):
	$(MAKE) -C $(SUBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(POBJ)
	$(MAKE) -C $(SUBDIR) clean

fclean:
	rm -f $(POBJ)
	rm -f $(NAME)
	$(MAKE) -C $(SUBDIR) fclean
	rm -f a.out

.PHONY: all re clean fclean
