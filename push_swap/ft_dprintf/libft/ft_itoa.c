/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:28:43 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:28:43 by leonmarq         ###   ########.fr       */
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
	s = ft_calloc(i + 1, sizeof(char));
	if (!s)
		return (NULL);
	s = transform(s, nl, i);
	return (s);
}
