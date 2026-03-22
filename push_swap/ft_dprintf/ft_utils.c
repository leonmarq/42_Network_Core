/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:40:24 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/22 11:02:54 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	dividecount(long long nb)
{
	int	i;

	i = 0;
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	findchrchr(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	findchr(const char *s, int i, char *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (set[x] == s[i])
			return (1);
		x++;
	}
	return (0);
}

int	strtonb(const char *s, int *i)
{
	int		start;
	int		x10;
	long	res;

	while (s[*i] == '0')
		(*i)++;
	start = *i;
	while (s[*i] >= '0' && s[*i] <= '9')
		(*i)++;
	x10 = 1;
	res = 0;
	while (*i > start)
	{
		(*i)--;
		res = res + ((s[*i] - '0') * x10);
		x10 = x10 * 10;
	}
	while (s[*i] >= '0' && s[*i] <= '9')
		(*i)++;
	return (res);
}

x_list	*emptylist(void)
{
	x_list	*res;

	res = malloc(sizeof(x_list));
	if (!res)
		return (res);
	res->set = ft_strdup("cspdiuxX%");
	res->setnb = ft_strdup("diuxX%");
	res->setnocp = ft_strdup("sdiuxX");
	if (!res->set || !res->setnb || !res->setnocp)
		return (NULL);
	res->type = 0;
	res->sraw = NULL;
	res->s = NULL;
	res->minus = 0;
	res->nul = 0;
	res->nbr = 0;
	res->precision = -1;
	res->next = NULL;
	return (res);
}
