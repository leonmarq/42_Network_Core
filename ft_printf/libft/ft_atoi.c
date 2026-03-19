/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:07:04 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:07:04 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	transform(const char *nptr, int si, int x10)
{
	long long	res;
	int			i;

	res = 0;
	i = si;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	i--;
	while (i >= si && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (nptr[i] - '0') * x10 + res;
		x10 = x10 * 10;
		i--;
	}
	if (res > (long long)2147483647 || res < (long long)-2147483648)
		return (0);
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	x10;

	i = 0;
	x10 = 1;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-')
	{
		x10 = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] == '0')
		i++;
	res = transform(nptr, i, x10);
	return (res);
}
