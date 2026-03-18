# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 13:33:44 by lmarquar          #+#    #+#              #
#    Updated: 2021/06/04 13:33:44 by lmarquar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Werror -Wall -Wextra
LFLAGS	:= -crs
BLFLAGS	:= -rvs
NAME	:= libft.a
SRC		:= ft_memset.c ft_memcpy.c ft_memccpy.c ft_bzero.c ft_atoi.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJ		:= $(SRC:.c=.o)
OBJB	:= $(SRCB:.c=.o)

all: $(NAME)

re: fclean all

$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC)

$(NAME): $(OBJ)
	ar $(LFLAGS) $@ $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)

.PHONY: re clean fclean all objects