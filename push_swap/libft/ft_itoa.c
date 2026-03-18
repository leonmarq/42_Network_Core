/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:29:23 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:29:23 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*transform(char *s, long nl, int leng)
{
	int		i;

	i = leng - 1;
	if (nl < 0)
	{
		s[0] = '-';
		nl = nl * -1;
	}
	while ((i >= 0 && s[0] != '-') || i > 0)
	{
		s[i] = (nl % 10) + '0';
		nl = nl / 10;
		i--;
	}
	s[leng] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*s;
	char	*res;
	long	nl;

	i = 0;
	if (n <= 0)
		i++;
	nl = n;
	while (nl != 0)
	{
		i++;
		nl = nl / 10;
	}
	nl = n;
	s = ft_calloc(i + 1, 1);
	res = transform(s, nl, i);
	return (res);
}
