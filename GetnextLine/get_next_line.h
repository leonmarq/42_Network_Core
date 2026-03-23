/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:54:07 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/21 14:20:15 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# define GNL_EOF_NO_DATA 0
# define GNL_LINE_COMPLETE 1
# define GNL_NEED_MORE 2
# define GNL_ERROR -1

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_line
{
	char	*s;
	size_t	len;
	size_t	cap;
}	t_line;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	free_n(char **p);

#endif
