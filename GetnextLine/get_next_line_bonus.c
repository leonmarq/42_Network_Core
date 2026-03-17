/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:53:35 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/17 14:09:50 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	grow_line(t_line *line, size_t add)
{
	size_t		i;
	size_t		nc;
	char		*s;

	i = 0;
	nc = line->cap;
	while (line->len + add + 1 > nc)
		nc *= 2;
	if (nc == line->cap)
		return (0);
	s = ft_calloc(nc, 1);
	if (!s)
		return (-1);
	while (i < line->len)
	{
		s[i] = line->s[i];
		i++;
	}
	free(line->s);
	line->s = s;
	line->cap = nc;
	return (0);
}

static int	append(t_line *line, char *buffer)
{
	size_t		use;
	size_t		i;
	size_t		j;

	use = 0;
	while (buffer[use] && buffer[use] != '\n')
		use++;
	if (buffer[use] == '\n')
		use++;
	if (grow_line(line, use) < 0)
		return (-1);
	i = -1;
	while (++i < use)
		line->s[line->len + i] = buffer[i];
	line->len += use;
	line->s[line->len] = 0;
	j = 0;
	while (buffer[use])
		buffer[j++] = buffer[use++];
	buffer[j] = 0;
	if (line->len && line->s[line->len - 1] == '\n')
		return (1);
	return (2);
}

static
int	createline(int fd, char *buffer, t_line *line)
{
	int	flag;

	flag = 2;
	while (flag > 1)
	{
		if (!buffer[0])
		{
			flag = read(fd, buffer, BUFFER_SIZE);
			if (flag < 0)
				return (-1);
			buffer[flag] = 0;
		}
		if (flag == 0 && line->len == 0)
			return (-2);
		if (flag > 0)
			flag = append(line, buffer);
	}
	return (flag);
}

char	*get_next_line(int fd)
{
	int			flag;
	t_line		line;
	static char	*buffer[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	line.cap = 32;
	line.len = 0;
	line.s = ft_calloc(line.cap, 1);
	if (!line.s)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer[fd])
		return (free(line.s), NULL);
	flag = createline(fd, buffer[fd], &line);
	if (flag > 0)
		return (line.s);
	free(buffer[fd]);
	buffer[fd] = NULL;
	if (flag < 0)
		return (free(line.s), NULL);
}
