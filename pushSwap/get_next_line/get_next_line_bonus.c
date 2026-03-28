/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:53:35 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/21 14:28:55 by leonmarq         ###   ########.fr       */
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
		return (GNL_ERROR);
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
		return (GNL_ERROR);
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
		return (GNL_LINE_COMPLETE);
	return (GNL_NEED_MORE);
}

static
int	createline(int fd, char *buffer, t_line *line)
{
	int	flag;

	flag = GNL_NEED_MORE;
	while (flag == GNL_NEED_MORE)
	{
		if (!buffer[0])
		{
			flag = read(fd, buffer, BUFFER_SIZE);
			if (flag < 0)
				return (GNL_ERROR);
			buffer[flag] = 0;
			if (flag == GNL_EOF_NO_DATA)
				return (GNL_EOF_NO_DATA);
		}
		flag = append(line, buffer);
	}
	return (flag);
}

int	default_line(t_line *l)
{
	l->cap = 32;
	l->len = 0;
	l->s = ft_calloc(l->cap, 1);
	if (!l->s)
		return (GNL_ERROR);
	return (0);
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
	if (default_line(&line) == GNL_ERROR)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer[fd])
		return (free(line.s), NULL);
	flag = createline(fd, buffer[fd], &line);
	if (flag > 0 || (flag == GNL_EOF_NO_DATA && line.len > 0))
	{
		if (flag == GNL_EOF_NO_DATA)
			free_n(&buffer[fd]);
		return (line.s);
	}
	free_n(&buffer[fd]);
	free_n(&line.s);
	return (NULL);
}
