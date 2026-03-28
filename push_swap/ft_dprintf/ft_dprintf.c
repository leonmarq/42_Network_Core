/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:40:05 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/27 09:26:48 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static
int	printlist(int fd, t_plist *list)
{
	int		size;
	char	nul;

	size = 0;
	nul = '\0';
	while (list)
	{
		if (list->type == 'c' && !list->sraw[0] && list->minus)
			size += write(fd, &nul, 1);
		if (list->s[0])
			size += write(fd, list->s, ft_strlen(list->s));
		if (list->type == 'c' && !list->sraw[0] && !list->minus)
			size += write(fd, &nul, 1);
		list = list->next;
	}
	return (size);
}

int	free_list(t_plist *list)
{
	t_plist	*t;

	while (list)
	{
		if (list->s && list->s != list->sraw)
			free(list->s);
		if (list->sraw)
			free(list->sraw);
		t = list;
		list = list->next;
		free(t);
	}
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_plist	*list;
	va_list	args;
	int		res;

	list = emptylist();
	if (!list)
		return (0);
	va_start(args, format);
	if (!filllist(list, format, args))
		return (free_list(list));
	va_end(args);
	if (!completelist(list))
		return (free_list(list));
	res = printlist(fd, list);
	free_list(list);
	return (res);
}
